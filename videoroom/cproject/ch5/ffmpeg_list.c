#include <stdio.h>
#include <libavutil/log.h>
#include <libavformat/avformat.h>

int main(int argc, char* arvg[])
{
    int ret;
    av_log_set_level(AV_LOG_INFO);

    AVIODirContext *ctx = NULL;
    AVIODirEntry *entry = NULL;

    ret = avio_open_dir(&ctx, "./", NULL);
    if(ret <0)
    {
        av_log(NULL,AV_LOG_ERROR,"Cant open dir:%s\n", av_err2str(ret));
        return -1;
    }
    while(1)
    {
        ret = avio_read_dir(ctx, &entry);
        if(ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR,"Cant read dir:%s\n", av_err2str(ret));
            goto __FAIL;
        }

        if(!entry){
          break;
      }
 
       av_log(NULL, AV_LOG_INFO,"%12"PRId64" %s \n", entry->size,entry->name);

        avio_free_directory_entry(&entry);
    }
    
__FAIL:
    avio_close_dir(&ctx);

    return 0;
}

