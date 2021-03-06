/*播放视频音频,多线程，实现音频时钟的音视频同步
 clang -g -o player4 player4.c `pkg-config --cflags --libs sdl2` -I/usr/local/ffmpeg/include -L/usr/local/ffmpeg/lib -l avutil -l avformat -l avcodec -l swresample -l swscale
./player4 dongman30.mp4
 * */
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <SDL.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000

#define MAX_AUDIOQ_SIZE (5 * 16 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 256 * 1024)

#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0

#define FF_REFRESH_EVENT (SDL_USEREVENT)
#define FF_QUIT_EVENT (SDL_USEREVENT + 1)

#define VIDEO_PICTURE_QUEUE_SIZE  1


typedef struct PacketQueue{
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

typedef struct VideoPicture{
    AVPicture  *bmp; 
    int width, height;  // source height & width
    int allocated;
    double pts;
} VideoPicture; 

/*contain all parames*/
typedef struct VideoState{
    // for multi-media file
    char                 filename[1024];
    AVFormatContext      *pFormatCtx;
    
    int                  videoStream, audioStream;

    // for audio
    AVStream             *audio_st;
    AVCodecContext       *audio_ctx;
    PacketQueue          audioq;
     // 解码后的音频缓冲区
    uint8_t              audio_buf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];
    unsigned int         audio_buf_size;
    unsigned int         audio_buf_index;
    AVFrame              audio_frame;
    AVPacket             audio_pkt;
    uint8_t              *audio_pkt_data; // 解码之前音频包的数据
    int                  audio_pkt_size;
    int                  audio_hw_buf_size;
    struct SwrContext    *audio_swr_ctx;

    double               audio_clock;
    double               video_clock; // pts of last decoded frame / predicted pts of next decoded frame

    double               frame_timer;      // next to post timer
    double               frame_last_pts;   // pts of last play video frame
    double               frame_last_delay; // delay of last play video frame

    // for video
    AVStream             *video_st;
    AVCodecContext       *video_ctx;
    PacketQueue          videoq;
    struct SwsContext    *video_sws_ctx;

    VideoPicture         pictq[VIDEO_PICTURE_QUEUE_SIZE];
    int                  pictq_size, pictq_rindex, pictq_windex;

    // for thread
    SDL_mutex            *pictq_mutex; // 锁
    SDL_cond             *pictq_cond;  // 信号量

    SDL_Thread           *parse_tid;   // 解复用线程
    SDL_Thread           *video_tid;   // 解码线程

    int                  quit;         // 退出事件
} VideoState;

SDL_mutex                *text_mutex;
SDL_Window               *win;
SDL_Renderer             *renderer;
SDL_Texture              *texture;

//FILE                     *audiofd = NULL;
//FILE                     *audiofd1 = NULL;

/* Since we only have one decoding thread, the Big Struct
   can be global in case we need it. */
VideoState *global_video_state;

void packet_queue_init(PacketQueue *q){
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}


int packet_queue_put(PacketQueue *q, AVPacket *pkt){
    AVPacketList *pkt1;
    if(av_dup_packet(pkt) < 0){
        return -1;
    }
    // AVPacketList是队列中的一个元素
    pkt1 = av_malloc(sizeof(AVPacketList));
    if(!pkt1)
        return -1;
    pkt1->pkt = *pkt;
    pkt1->next = NULL;

    SDL_LockMutex(q->mutex); // 上锁

    if(!q->last_pkt){
        q->first_pkt = pkt1;
    }else{
        q->last_pkt->next = pkt1;
    }

    q->last_pkt = pkt1; // 更新队尾元素
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    fprintf(stderr, "enqueue, packets:%d, send cond signal\n", q->nb_packets);
    SDL_CondSignal(q->cond); // 发送信号量唤醒等待元素的线程

    SDL_UnlockMutex(q->mutex); // 解锁。这句实际上是先解锁，发送信号，再加锁，再解锁
    return 0;
}

int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block){
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex); // 加锁

    for(;;){
        if(global_video_state->quit){
            fprintf(stderr, "quit from queue_get\n");
            ret = -1;
            break;
        }

        pkt1 = q->first_pkt; // 拿到队列头
        if(pkt1){
            q->first_pkt = pkt1->next;
            if(!q->first_pkt)
                q->last_pkt = NULL;
            q->nb_packets--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1); // 释放元素空间
            ret = 1;
            break;
        }else if(!block){
            ret = 0;
            break;
        }else{
            fprintf(stderr, "queue is empty, so wait a moment and wait a cond signal\n");
            SDL_CondWait(q->cond, q->mutex); // 先解锁，收到信号再加锁，再解锁
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}

double get_audio_clock(VideoState *is){
    double pts;
    int hw_buf_size, bytes_per_sec, n;

    pts = is->audio_clock; // maintained in the audio thread
    hw_buf_size = is->audio_buf_size - is->audio_buf_index;
    bytes_per_sec = 0;
    n = is->audio_ctx->channels * 2;
    if(is->audio_st){
        bytes_per_sec = is->audio_ctx->sample_rate * n;
    }
    if(bytes_per_sec){
        pts -= (double)hw_buf_size / bytes_per_sec;
    }
    return pts;
}

int audio_decode_frame(VideoState *is, uint8_t *audio_buf, int buf_size, double *pts_ptr){
    
    int len1, data_size = 0;
    AVPacket *pkt = &is->audio_pkt;
    double pts;
    int n;

    for(;;){
        while(is->audio_pkt_size > 0){
            int got_frame = 0;
            len1 = avcodec_decode_audio4(is->audio_ctx, &is->audio_frame, &got_frame, pkt);
            if(len1 < 0){
                fprintf(stderr, "Failed to decode audio ... ...\n");
                is->audio_pkt_size = 0;
                break;
            }
        
            data_size = 0;
            if(got_frame){
                data_size = 2 * 2 * is->audio_frame.nb_samples;

                assert(data_size <= buf_size);
                swr_convert(is->audio_swr_ctx,
                        &audio_buf,
                        MAX_AUDIO_FRAME_SIZE*3/2,
                        (const uint8_t **)is->audio_frame.data,
                        is->audio_frame.nb_samples);
                //memcpy(audio_buf, frame.data[0], data_size);
                //fwrite(audio_buf, 1, data_size, audiofd);
                //fflush(audiofd);
            }

            is->audio_pkt_data += len1;
            is->audio_pkt_size -= len1;

            if(data_size <= 0){
                continue;
            }
            pts = is->audio_clock;
            *pts_ptr = pts;
            n = 2 * is->audio_ctx->channels;
            is->audio_clock += (double)data_size /
                (double)(n * is->audio_ctx->sample_rate);
            return data_size;
        }

        if(pkt->data)
            av_free_packet(pkt);

        if(is->quit){
            fprintf(stderr, "will quit program... ...\n");
            return -1;
        }

        if(packet_queue_get(&is->audioq, pkt, 1) < 0){
            return -1;
        }
        is->audio_pkt_data = pkt->data;
        is->audio_pkt_size = pkt->size;

        // if update, update the audio clock
        if(pkt->pts != AV_NOPTS_VALUE){
            is->audio_clock = av_q2d(is->audio_st->time_base)*pkt->pts;
        }
    }
}


void audio_callback(void *userdata, Uint8 *stream, int len){
    VideoState *is = (VideoState *)userdata;
    int len1, audio_size;
    double pts;

    SDL_memset(stream, 0, len);

    while(len > 0){
        if(is->audio_buf_index >= is->audio_buf_size){
            audio_size = audio_decode_frame(is, is->audio_buf, sizeof(is->audio_buf), &pts);
            if(audio_size < 0){ // if error, output silence
                is->audio_buf_size = 1024*2*2;
                memset(is->audio_buf, 0, is->audio_buf_size);
            }else{
                is->audio_buf_size = audio_size;
            }
            is->audio_buf_index = 0;
        }
        len1 = is->audio_buf_size - is->audio_buf_index;
        fprintf(stderr, "stream addr:%p, audio_buf_index:%d, audio_buf_size:%d, len1:%d, len:%d\n",
                stream,
                is->audio_buf_index,
                is->audio_buf_size,
                len1,
                len);

        if(len1 > len)
            len1 = len;
        
        //memcpy(stream, (uint8_t *)is->audio_buf + is->audio_buf_index, len1);
        //fwrite(is->audio_buf, 1, len1, audiofd1);
        //fflush(audiofd1);
        SDL_MixAudio(stream, (uint8_t *)is->audio_buf + is->audio_buf_index, len1, SDL_MIX_MAXVOLUME);
        len -= len1;
        stream += len1;
        is->audio_buf_index += len1;
    }
}

/* video decode callback*/
static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque){
    SDL_Event event;
    event.type = FF_REFRESH_EVENT;
    event.user.data1 = opaque;
    SDL_PushEvent(&event);
    return 0;  // stop timer
}

/* schedule a video refresh in 'delay' ms */
static void schedule_refresh(VideoState *is, int delay){
    SDL_AddTimer(delay, sdl_refresh_timer_cb, is);
}

void video_display(VideoState *is){
    
    SDL_Rect rect;
    VideoPicture *vp;
    float aspect_ratio;
    int w, h, x, y;
    int i;

    vp = &is->pictq[is->pictq_rindex];
    if(vp->bmp){

        SDL_UpdateYUVTexture(texture, NULL,
                vp->bmp->data[0], vp->bmp->linesize[0],
                vp->bmp->data[1], vp->bmp->linesize[1],
                vp->bmp->data[2], vp->bmp->linesize[2]);

        rect.x = 0;
        rect.y = 0;
        rect.w = is->video_ctx->width;
        rect.h = is->video_ctx->height;
        // SDL_LockMutex(text_mutex);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        // SDL_UnlockMutex(text_mutex);
    }
}

/* 视频渲染  */
void video_refresh_timer(void *userdata){
    VideoState *is = (VideoState *) userdata;
    VideoPicture *vp;
    double actual_delay, delay, sync_threshold,ref_clock,diff;

    if(is->video_st){
        if(is->pictq_size == 0){
            schedule_refresh(is, 1);
        } else{ // data is not NULL;
            vp = &is->pictq[is->pictq_rindex];

            delay = vp->pts - is->frame_last_pts; // the pts from last time
            if(delay <= 0 || delay >= 1.0){
                delay = is->frame_last_delay; // time over 1s,this is incorrect delay, use previous one
            }

            // save for next time
            is->frame_last_delay = delay;
            is->frame_last_pts = vp->pts;

            // update delay to sync to audio
            ref_clock = get_audio_clock(is); // 音频参考时钟
            diff = vp->pts - ref_clock;
            
            /*Skip or repeat the frame. Take delay into account
             * FFPlay stil doesn't know if this is the best guess.*/
            sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
            if(fabs(diff) < AV_NOSYNC_THRESHOLD){
                if(diff <= -sync_threshold){
                    delay = 0;
                }else if(diff >= sync_threshold){
                    delay = 2 * delay;
                }
            }
            is->frame_timer += delay;
            // computer the real delay
            actual_delay = is->frame_timer - (av_gettime() / 1000000.0);
            if(actual_delay < 0.010){
                // Really it should skip the picture instead
                actual_delay = 0.010;
            }

            schedule_refresh(is, (int)(actual_delay * 1000 + 0.5)); // resend timer

            // show the picture
            video_display(is);

            // update queue for next picture
            if(++is->pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE){
                is->pictq_rindex = 0;
            }
            SDL_LockMutex(is->pictq_mutex);
            is->pictq_size--;
            SDL_CondSignal(is->pictq_cond);
            SDL_UnlockMutex(is->pictq_mutex);
        }
    } else{
        schedule_refresh(is, 100);
    }
}

void alloc_picture(void *userdata){

    int ret = -1;
    VideoState *is = (VideoState *)userdata;
    VideoPicture *vp;

    vp = &is->pictq[is->pictq_windex];
    if(vp->bmp){
        avpicture_free(vp->bmp);
        free(vp->bmp);

        vp->bmp = NULL;
    }

    // Allocate a place to put our YUV image on that screen
    // SDL_LockMutex(text_mutex);
    vp->bmp = (AVPicture*)malloc(sizeof(AVPicture));
    ret = avpicture_alloc(vp->bmp,
                AV_PIX_FMT_YUV420P,
                is->video_ctx->width,
                is->video_ctx->height);
    if(ret < 0){
        fprintf(stderr, "Could not allocate temporary picture: %s\n", av_err2str(ret));
    }
    // SDL_UnLockMutex(text_mutex);

    vp->width = is->video_ctx->width;
    vp->height = is->video_ctx->height;
    vp->allocated = 1;
}

int queue_picture(VideoState *is, AVFrame *pFrame, double pts){
    
    VideoPicture *vp;

    /* wait until we have space for a new pic */
    SDL_LockMutex(is->pictq_mutex);
    while(is->pictq_size >= VIDEO_PICTURE_QUEUE_SIZE && !is->quit){
        SDL_CondWait(is->pictq_cond, is->pictq_mutex);
    }
    SDL_UnlockMutex(is->pictq_mutex);
    
    if(is->quit){
        fprintf(stderr, "quit from queue_picture... ...\n");
        return -1;
    }

    // windex is set to 0 initially
    vp = &is->pictq[is->pictq_windex];
    
    // allocate or resize the buffer
    if(!vp->bmp || vp->width != is->video_ctx->width || vp->height != is->video_ctx->height){

        vp->allocated = 0;
        alloc_picture(is);
        if(is->quit){
            fprintf(stderr, "quit from queue_picture2...\n");
            return -1;
        }
    }

    // we have a place to put our picture on the queue
    if(vp->bmp){

        vp->pts = pts;
        // Convert the image into YUV format that SDL uses
        sws_scale(is->video_sws_ctx, (uint8_t const * const *)pFrame->data,
                pFrame->linesize, 0, is->video_ctx->height,
                vp->bmp->data, vp->bmp->linesize);

        // now we inform our display thread that we have a pic ready
        if(++is->pictq_windex == VIDEO_PICTURE_QUEUE_SIZE){
            is->pictq_windex = 0;
        }
        SDL_LockMutex(is->pictq_mutex);
        is->pictq_size++;
        SDL_UnlockMutex(is->pictq_mutex);
    }
    return 0;
}

double synchronize_video(VideoState *is, AVFrame *src_frame, double pts){
    
    double frame_delay;

    if(pts != 0){
        // if have pts,set video clock to it
        is->video_clock = pts;
    }else{
        // if no pts, set it to the clock
        pts = is->video_clock;
    }
    // update the video clock
    frame_delay = av_q2d(is->video_ctx->time_base);
    frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
    is->video_clock += frame_delay;
    return pts;
}

int decode_video_thread(void *arg){
    VideoState *is = (VideoState *)arg;
    AVPacket pkt1, *packet = &pkt1;
    int frameFinished;
    AVFrame *pFrame;
    double pts;

    pFrame = av_frame_alloc();

    for(;;){
        if(packet_queue_get(&is->videoq, packet, 1) < 0){
            // means we quit getting packets
            break;
        }
        pts = 0;

        // Decode video frame
        avcodec_decode_video2(is->video_ctx, pFrame, &frameFinished, packet);
        if((pts = av_frame_get_best_effort_timestamp(pFrame)) == AV_NOPTS_VALUE){
            pts =0;
        }
        pts *= av_q2d(is->video_st->time_base);

        if(frameFinished){
            pts = synchronize_video(is, pFrame, pts);
            if(queue_picture(is, pFrame, pts) < 0){  // 解码后放入解码后的队列
                break;
            }
        }

        av_free_packet(packet);
    }
    av_frame_free(&pFrame);
    return 0;
}

int stream_component_open(VideoState *is, int stream_index){
    
    AVFormatContext *pFormatCtx = is->pFormatCtx;
    AVCodecContext *codecCtx = NULL;
    AVCodec *codec = NULL;
    SDL_AudioSpec wanted_spec, spec;

    if(stream_index < 0 || stream_index >= pFormatCtx->nb_streams){
        return -1;
    }

    codecCtx = avcodec_alloc_context3(NULL);

    int ret = avcodec_parameters_to_context(codecCtx, pFormatCtx->streams[stream_index]->codecpar);
    if(ret < 0){
        return -1;
    }
    codec = avcodec_find_decoder(codecCtx->codec_id);

    if(!codec){
        fprintf(stderr, "Unsupported codec!\n");
        return -1;
    }

    if(codecCtx->codec_type == AVMEDIA_TYPE_AUDIO){
        // Set audio settings from codec info
        wanted_spec.freq  = codecCtx->sample_rate;
        wanted_spec.format = AUDIO_S16SYS;
       // wanted_spec.channels = codecCtx->channels;
        wanted_spec.channels = 2;
        wanted_spec.silence = 0;
        wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
        wanted_spec.callback = audio_callback;
        wanted_spec.userdata = is;
        
        // open audio device
        if(SDL_OpenAudio(&wanted_spec, &spec) < 0){
            fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
            return -1;
        }
        is->audio_hw_buf_size = spec.size;
    }

    // open audio/video decode
    if(avcodec_open2(codecCtx, codec, NULL) < 0){
        fprintf(stderr, "Unsupported codec!\n");
        return -1;
    }

    switch(codecCtx->codec_type){
        case AVMEDIA_TYPE_AUDIO:
            is->audioStream = stream_index;
            is->audio_st = pFormatCtx->streams[stream_index];
            is->audio_ctx = codecCtx;
            is->audio_buf_size = 0;
            is->audio_buf_index = 0;
            memset(&is->audio_pkt, 0, sizeof(is->audio_pkt));
            packet_queue_init(&is->audioq);

            // Out Audio Param
            uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;

            int out_nb_samples = is->audio_ctx->frame_size;
            int out_sample_rate = is->audio_ctx->sample_rate;
            int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
            int64_t in_channel_layout = av_get_default_channel_layout(is->audio_ctx->channels);

            struct SwrContext *audio_convert_ctx = NULL;
            audio_convert_ctx = swr_alloc();
            if(!audio_convert_ctx){
                printf("Failed to swr_alloc\n");
                return -1;
            }

            // 重采样初始化
            swr_alloc_set_opts(audio_convert_ctx,
                       out_channel_layout,
                       AV_SAMPLE_FMT_S16,
                       out_sample_rate,
                       in_channel_layout,
                       is->audio_ctx->sample_fmt,
                       is->audio_ctx->sample_rate,
                       0,
                       NULL);

             fprintf(stderr, "swr opts: out_channel_layout:%lld, out_sample_fmt:%d, out_sample_rate:%d, in_channel_layout:%lld, in_sample_fmt:%d, in_sample_rate:%d\n", out_channel_layout, 
		    AV_SAMPLE_FMT_S16, 
		    out_sample_rate, 
		    in_channel_layout, 
            is->audio_ctx->sample_fmt,
            is->audio_ctx->sample_rate);

            swr_init(audio_convert_ctx);
            is->audio_swr_ctx = audio_convert_ctx;
            SDL_PauseAudio(0);

            break;

        case AVMEDIA_TYPE_VIDEO:
            is->videoStream = stream_index;
            is->video_st = pFormatCtx->streams[stream_index];
            is->video_ctx = codecCtx;

            is->frame_timer = (double)av_gettime() / 1000000.0;
            is->frame_last_delay = 40e-3;

            packet_queue_init(&is->videoq);
            is->video_tid = SDL_CreateThread(decode_video_thread, "video_thread", is);

            is->video_sws_ctx = sws_getContext(is->video_ctx->width, 
				 is->video_ctx->height,
				 is->video_ctx->pix_fmt, 
				 is->video_ctx->width,
				 is->video_ctx->height, 
				 AV_PIX_FMT_YUV420P,
				 SWS_BILINEAR, 
				 NULL, NULL, NULL);
            break;
        default:
            break;
    }
}

/* 解复用线程 */
int demux_thread(void *arg){
    
    Uint32 pixformat;

    VideoState *is = (VideoState *)arg;
    AVFormatContext *pFormatCtx = NULL;
    AVPacket pkt1, *packet = &pkt1;

    int i;
    int video_index = -1;
    int audio_index = -1;

    is->videoStream = -1;
    is->audioStream = -1;

    global_video_state = is;

    // Open video file
    if(avformat_open_input(&pFormatCtx, is->filename, NULL, NULL) != 0)
        return -1;

    is->pFormatCtx = pFormatCtx;

    //Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return -1;

    // Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, is->filename, 0);

    // Find the first video stream
    for(i=0; i < pFormatCtx->nb_streams; i++){
         if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && video_index < 0){
             video_index = i;
         }
 
         if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audio_index < 0){
             audio_index = i;
         }
     }

    if(audio_index >= 0){
        stream_component_open(is, audio_index);
    }

    if(video_index >= 0){
        stream_component_open(is, video_index);
    }
 
    if(is->videoStream < 0 || is->audioStream < 0){
        fprintf(stderr, "%s : could not open codecs\n", is->filename);
        goto fail;
    }

    fprintf(stderr, "video context: width=%d, height=%d\n", is->video_ctx->width, is->video_ctx->height);
    win = SDL_CreateWindow("Media Player v4.0_syn",
             SDL_WINDOWPOS_UNDEFINED,
             SDL_WINDOWPOS_UNDEFINED,
             is->video_ctx->width, is->video_ctx->height,
             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(win, -1, 0);

     pixformat = SDL_PIXELFORMAT_IYUV;
     texture = SDL_CreateTexture(renderer,
             pixformat,
             SDL_TEXTUREACCESS_STREAMING,
             is->video_ctx->width,
             is->video_ctx->height);

     // main decode loop
     for(;;){
        if(is->quit){
            SDL_CondSignal(is->videoq.cond);
            SDL_CondSignal(is->audioq.cond);
            break;
        }

        // seek stuff goes here
        if(is->audioq.size > MAX_AUDIOQ_SIZE ||
                is->videoq.size > MAX_VIDEOQ_SIZE){
            SDL_Delay(10);
            continue;
        }

        if(av_read_frame(is->pFormatCtx, packet) < 0){
            if(is->pFormatCtx->pb->error == 0){
                SDL_Delay(100);
                continue;
            } else {
                break;
            }
        }

        // Is this a packet from the video stream?
        if(packet->stream_index == is->videoStream){
            packet_queue_put(&is->videoq, packet);
            fprintf(stderr, "put video queue, size :%d\n", is->videoq.nb_packets);
        } else if(packet->stream_index == is->audioStream){
            packet_queue_put(&is->audioq, packet);
            fprintf(stderr, "put audio queue, size :%d\n", is->audioq.nb_packets);
        } else{
            av_free_packet(packet);
        }
     }

     // all done ,wait for it
     while(!is->quit){
        SDL_Delay(100);
     }

 fail:
     if(1){
        SDL_Event event;
        event.type = FF_QUIT_EVENT;
        event.user.data1 = is;
        SDL_PushEvent(&event);
     }

     return 0;
}

int main(int argc, char *argv[]){
    int     ret = -1;

    SDL_Event event;

    VideoState  *is;

    //big struct, it's core 
    is = av_mallocz(sizeof(VideoState));

    if(argc < 2){
        fprintf(stderr, "Usage: command <file>\n");
        exit(1);
    }

    // Register all formats and codecs
    av_register_all();

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }

    text_mutex = SDL_CreateMutex();

    av_strlcpy(is->filename, argv[1], sizeof(is->filename));

    is->pictq_mutex = SDL_CreateMutex();
    is->pictq_cond = SDL_CreateCond();

    //set timer，ever 40ms send timer and post callback 
    schedule_refresh(is, 40);

    is->parse_tid = SDL_CreateThread(demux_thread, "demux_thread", is);
    if(!is->parse_tid) {
        av_free(is);
        goto __FAIL;
    }

    for(;;) {

        SDL_WaitEvent(&event);
        switch(event.type) {
            case FF_QUIT_EVENT:
            case SDL_QUIT:
                fprintf(stderr, "receive a QUIT event: %d\n", event.type);
                is->quit = 1;
                SDL_CondSignal(is->audioq.cond);
                SDL_CondSignal(is->pictq_cond);
                //SDL_Quit();
                //return 0;
                goto __QUIT;
                break;
            case FF_REFRESH_EVENT:
                //fprintf(stderr, "receive a refresh event: %d\n", event.type);
                video_refresh_timer(event.user.data1);
                break;
            default:
                break;
        }
    }

__QUIT:
    ret = 0;


__FAIL:
    SDL_Quit();
    /*
    if(audiofd){
        fclose(audiofd);
    }
    if(audiofd1){
        fclose(audiofd1);
    }
    */
    return ret;
}
