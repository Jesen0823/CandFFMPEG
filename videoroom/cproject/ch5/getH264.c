// get H264 file from a video 
#include <stdio.h>
#include <libavutil/log.h>
#include <libavformat/avio.h>
#include <libavformat/avformat.h>

#ifndef AV_WB32
#   define AV_WB32(p, val) do {                 \
        uint32_t d = (val);                     \
        ((uint8_t*)(p))[3] = (d);               \
        ((uint8_t*)(p))[2] = (d)>>8;            \
        ((uint8_t*)(p))[1] = (d)>>16;           \
        ((uint8_t*)(p))[0] = (d)>>24;           \
    } while(0)
#endif

#ifndef AV_RB16
#   define AV_RB16(x)                           \
    ((((const uint8_t*)(x))[0] << 8) |          \
      ((const uint8_t*)(x))[1])
#endif


static int alloc_and_copy(AVPacket *out,
        const uint8_t *sps_pps, uint32_t sps_pps_size,
        const uint8_t *in, uint32_t in_size)
{
    uint32_t offset = out->size;
    uint8_t nal_header_size = offset ？ 3 ： 4;
    int err;

    // 给packet扩容
    err = av_grow_packet(out, sps_pps_size + in_size + nal_header_size);
    if(err < 0)
        return err;

    if(sps_pps)
        memcpy(out->data + offset, sps_pps, sps_pps_size);
    memcpy(out->data + sps_pps_size + nal_header_size + offset, in, in_size);
    if(!offset){
        AV_WB32(out->data + sps_pps_size, 1);
    }else{
        (out->data + offset + sps_pps_size)[0] =
        (out->data + offset + sps_pps_size)[1] = 0;
        (out->data + offset + sps_pps_size)[2] = 1;
    }
    return 0;
}

// 读取sps和pps
int h264_extradata_to_annexb(const uint8_t *codec_extradata, const int codec_extradata_size,AVPacket *out_extradata, int padding)
{
    uint16_t unit_size  = 0;
    uint64_t total_size = 0;
    uint8_t *out        = NULL;
    uint8_t unit_nb     = 0;
    uint8_t sps_done    = 0;
    uint8_t sps_seen    = 0;
    uint8_t pps_seen    = 0;
    uint8_t sps_offset  = 0;
    uint8_t pps_offset  = 0;

    // extradata存放数据格式如上，前4个字节没用，所以舍弃
    const uint8_t *extradata = codec_extradata + 4;
    // 每个H264裸数据都是以 0001 四个字节开头的
    static const uint8_t nalu_header[4] = {0,0,0,1};
   
   // 跳过一个字节，没用
   // extradata++;
   // 表示编码长度需要字节数
    int length_size = *(extradata++ & 0x3) + 1;

    sps_offset = pps_offset = -1;

    // retrieve sps and pps unit
    unit_nb = *extradata++ & 0x1f; // 获取sps个数
    if(!unit_nb){
        goto pps;
    }else{
        sps_offset = 0;
        sps_seen = 1;
    }

    while(unit_nb--){
        int err;

        // AV_RB16函数读取两字节
        unit_size  = AV_RB16(extradata);
        // 加4字节h264的header也就是0001
        total_size += unit_size + 4;
        if(total_size > INT_MAX - padding){
            av_log(NULL, AV_LOG_ERROR, "Too big extradata size, corrupted stream or invalid MP4/AVCC bitstream\n");
            av_free(out);
            return AVERROR(EINVAL);
        }

        //2:表示上面 unit_size 的所占字结数
        //这句的意思是 extradata 所指的地址，加两个字节，再加 unit 的大小所指向的地址
        //是否超过了能访问的有效地址空间
        if(extradata + 2 + unit_size > codec_extradata + codec_extradata_size){
        av_log(NULL, AV_LOG_ERROR, "Packet header is not contained in global extradata, corrupted stream or invalid MP4/AVCC bitstream\n");
        av_free(out);
        return AVERROR(EINVAL);
        }

        //分配存放sps的空间
        if((err = av_reallocp(&out, total_size + padding)) < 0)
            return err;
        memcpy(out + total_size - unit_size - 4, nalu_header, 4);
        memcpy(out + total_size - unit_size, extradata + 2, unit_size);
        extradata += 2 + unit_size;

pps:
        // sps处理完成后处理pps
        if(!unit_nb && !sps_done++){
            // number od pps units
            unit_nb = *extradata++;
            if(unit_nb){
                pps_offset = total_size;
                pps_seen = 1;
            }
        }
    }

    // 余下空间清0
    if(out){
        memset(out + total_size, 0, padding);
    }

    if(!sps_seen)
        av_log(NULL, AV_LOG_WARNING, "Warning:SPS NALU missing or invalid. The resulting stream may not play.\n");

    if(!pps_seen)
        av_log(NULL, AV_LOG_WARNING, "Warning: PPS NALU missing or invalid. The resulting stream may not play.\n");

    out_extradata->data   = out;
    out_extradata->size   = total_size;
    return 0;
}

int h264_mp4toanexb(AVFormatContext *fmt_ctx, AVPacket *in, FILE *dst_fd)
{
    AVPacket *out = NULL;
    AVPacket spspps_pkt;

    int len;
    uint8_t unit_type;
    int32_t nal_size;
    uint32_t cumul_size = 0;
    const uint8_t *buf;
    const uint8_t *buf_end;
    int buf_size;
    int ret = 0,i;

    //create a AVPacket
    out = av_packet_alloc();

    buf = in->data;
    buf_size = in->size;
    buf_end = in->data + in->size;

    do{
        ret = AVERROR(EINVAL);
        //因为每个视频帧的前 4 个字节是视频帧的长度
        //如果buf中的数据都不能满足4字节，所以后面就没有必要再进行处理了
        if(buf + 4 > buf_end){
            goto fail;
        }

         //将前四字节转换成整型,也就是取出视频帧长度
        for(nal_size = 0, i = 0; i < 4; i++)
            nal_size = (nal_size << 8) | buf[i];

        buf += 4;// 后移4个字节,也就是视频帧长度），从而指向真正的视频帧数据
        unit_type = *buf & 0x1f; //视频帧的第一个字节里后5位，有NAL TYPE，即nal单元的类型

        //如果视频帧长度大于从 AVPacket 中读到的数据大小，说明这个数据包肯定是出错了
        if(nal_size > buf_end - buf || nal_size < 0)
            goto fail;

        if(unit_type == 5){  //关键帧
            //在每个I帧之前都加 SPS/PPS
            h264_extradata_to_annexb(fmt_ctx->streams[in->stream_index] ->codecpar->extradata,
                    fmt_ctx->streams[in->stream_index] ->codecpar->extradata_size,
                    &spspps_pkt,
                    AV_INPUT_BUFFER_PADDING_SIZE);
            if((ret = alloc_and_copy(out, spspps_pkt.data, spspps_pkt.size, buf, nal_size)) < 0){
                goto fail;
            }
        }else{
            if((ret = alloc_and_copy(out,NULL,0,buf,nal_size)) < 0){
                goto fail;
            }
        }
        
        len = fwrite(out->data, 1, out->size, dst_fd);
        if(len != out->size){
            av_log(NULL, AV_LOG_DEBUG,"warning, length of writed data isn`t equal pkt.size(%d, %d)\n",
                    len,
                    out->size);
        }
        fflush(dst_fd);

next_nal:
        buf += nal_size;
        cumul_size += nal_size + 4;
    }while(cumul_size < buf_size);

fail:
    //av_packet_free(&out);
    return ret;
}

int main(int argc, char*  argv[])
{
    int err_code;
    char errors[1024];

    char *src_filename = NULL;
    char *dst_filename = NULL;

    FILE *dst_fd = NULL;
    int video_stream_index = -1;

    AVFormatContext *fmt_cxt = NULL;
    AVPacket pkt;

    av_log_set_level(AV_LOG_DEBUG);
    

    //1.read two params from console
    if(argc < 3){
        av_log(NULL, AV_LOG_ERROR, "params is error.\n");
        return -1;
    }

    src_filename = argv[1];
    dst_filename = argv[2];
    if(src_filename == NULL || dst_filename == NULL){
        av_log(NULL,AV_LOG_ERROR,"src or dst is null.\n");
        return -1;
    }

    dst_fd = fopen(dst_filename, "wb");
    if(!dst_fd){
        av_log(NULL, AV_LOG_DEBUG, "Could not open destination file %s\n", dst_filename);
        return -1;
    }

    //av_register_all();

   /*open input media file, and allocate format context*/
    if((err_code = avformat_open_input(&fmt_cxt,src_filename,NULL,NULL)) < 0){
        av_strerror(err_code, errors,1024);
        av_log(NULL, AV_LOG_DEBUG, "Can,t open file:%s, %d(%s)\n", src_filename,err_code,errors);
        return -1;
    }
    
    /*dump input information*/
    av_dump_format(fmt_cxt,0,src_filename,0);

    /*init packet*/
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    /*find best video stream*/
    video_stream_index = av_find_best_stream(fmt_cxt, AVMEDIA_TYPE_VIDEO, -1, -1,NULL, 0);
    if(video_stream_index < 0){
        av_log(NULL, AV_LOG_DEBUG, "Could not find %s stream in input file %s\n",
                av_get_media_type_string(AVMEDIA_TYPE_VIDEO),
                src_filename);
        return AVERROR(EINVAL);
    }

    while(av_read_frame(fmt_cxt, &pkt) >= 0){
        if(pkt.stream_index == video_stream_index){
            h264_mp4toannexb(fmt_cxt, &pkt, dst_fd);
        }
        // release pkt->data
        //av_packet_unref(&pkt);
    }

    //close input media file
    avformat_close_input(&fmt_cxt);
    if(dst_fd){
        fclose(dst_fd);
    }

    return 0;
}
