#include <libavformat/avformat.h>
int main(int argc, char *argv[])

{
    int ret2;
    ret2 = avpriv_io_move("1.txt","2.txt");
    if(ret2 < 0)
    {
        av_log(NULL,AV_LOG_ERROR,"move failed!\n");
        return -1;
    }
    av_log(NULL,AV_LOG_INFO,"move success\n");


    int ret;
    ret = avpriv_io_delete("./mytestfile.txt");
    if(ret < 0)
    {
        av_log(NULL,AV_LOG_ERROR,"delete ret failed!\n");
        return -1;
    }
    av_log("success delete file.");
    return 0;
}

