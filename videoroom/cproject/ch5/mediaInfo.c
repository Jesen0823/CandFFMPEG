// print mediainfo demo 
#include <libavutil/log.h>
#include <libavformat/avformat.h>

int main(int argc, char*  argv[])
{
    int ret;
    AVFormatContext *fmt_cxt = NULL;

    av_log_set_level(AV_LOG_INFO);
    
    //av_register_all();

    ret = avformat_open_input(&fmt_cxt, "./tv6.mp4",NULL,NULL);
    if(ret < 0){
        av_log(NULL, AV_LOG_ERROR, "Can,t open file:%s\n", av_err2str(ret));
        return -1;
    }

    av_dump_format(fmt_cxt, 0, "./tv6.mp4",0);

    

    avformat_close_input(&fmt_cxt);


    return 0;
}
