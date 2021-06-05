// get aac file from a video 
#include <stdio.h>
#include <libavutil/log.h>
#include <libavformat/avformat.h>

int main(int argc, char*  argv[])
{
    int ret;
    int audio_index;
    int len;

    char* src = NULL;
    char* dst = NULL;
    AVFormatContext *fmt_cxt = NULL;
    AVPacket pkt;

    av_log_set_level(AV_LOG_INFO);
    
    //av_register_all();

    //1.read two params from console
    if(argc < 3){
        av_log(NULL, AV_LOG_ERROR, "params is error.\n");
        return -1;
    }

    src = argv[1];
    dst = argv[2];
    if(!src || !dst){
        av_log(NULL,AV_LOG_ERROR,"src or dst is null.\n");
    }


    ret = avformat_open_input(&fmt_cxt, src,NULL,NULL);
    if(ret < 0){
        av_log(NULL, AV_LOG_ERROR, "Can,t open file:%s\n", av_err2str(ret));
        return -1;
    }

    FILE* dst_fd = fopen(dst,"wb");
    if(!dst_fd){
        av_log(NULL, AV_LOG_ERROR, "Can,t open out file！/n");
        avformat_close_input(&fmt_cxt);
        return -1;
    }

    av_dump_format(fmt_cxt, 0, src, 0);

    //2. get stream 
    ret = av_find_best_stream(fmt_cxt, AVMEDIA_TYPE_AUDIO,-1,-1,NULL,0);
    if(ret < 0){
        av_log(NULL,AV_LOG_ERROR,"can,t find the best stream.\n");
        avformat_close_input(&fmt_cxt);
        fclose(dst_fd);
        return -1;
    }
    audio_index = ret;

    //3.write audio data to a aac file
    av_init_packet(&pkt);
   
    while(av_read_frame(fmt_cxt, &pkt) >= 0){
        if(pkt.stream_index == audio_index){
            len = fwrite(pkt.data, 1, pkt.size, dst_fd);
            if(len != pkt.size){
                av_log(NULL, AV_LOG_WARNING,"warning,length of data is not equal size of pkt.\n");
            }
        }

        av_packet_unref(&pkt);
    }   

    avformat_close_input(&fmt_cxt);
    if(dst_fd){
        fclose(dst_fd);
    }

    return 0;
}
