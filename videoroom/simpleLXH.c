/**
* 最简单的基于FFmpeg的解码器
* Simplest FFmpeg Decoder
*
* 雷霄骅 Lei Xiaohua
* leixiaohua1020@126.com
* 中国传媒大学/数字电视技术
* Communication University of China / Digital TV Technology
* http://blog.csdn.net/leixiaohua1020
*
* 本程序实现了视频文件的解码(支持HEVC，H.264，MPEG2等)。
* 是最简单的FFmpeg视频解码方面的教程。
* 通过学习本例子可以了解FFmpeg的解码流程。
* This software is a simplest video decoder based on FFmpeg.
* Suitable for beginner of FFmpeg.
*
*/
 
#include <stdio.h>
#include "stdafx.h"
 
#define __STDC_CONSTANT_MACROS
 
#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
};
#endif
#endif
 
 
int main(int argc, char* argv[])
{
	AVFormatContext *pFormatCtx;
	int             i, videoindex;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame *pFrame, *pFrameYUV;
	uint8_t *out_buffer;
	AVPacket *packet;
	int y_size;
	int ret, got_picture;
	struct SwsContext *img_convert_ctx;
	//输入文件路径
	char filepath[] = "tese1_3.ts";
	//创建两个解码后的输出文件
	FILE *fp_yuv = fopen("output.yuv", "wb+");
	FILE *fp_h264 = fopen("output.h264", "wb+");
 
	av_register_all();//注册所有组件
	avformat_network_init();//初始化网络
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext
 
	if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {//打开输入的视频文件
		printf("Couldn't open input stream.\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL)<0) {//获取视频文件信息
		printf("Couldn't find stream information.\n");
		return -1;
	}
	videoindex = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoindex = i;
			break;
		}
	}
	if (videoindex == -1) {
		printf("Didn't find a video stream.\n");
		return -1;
	}
 
	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);//查找解码器
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec, NULL)<0) {//打开解码器
		printf("Could not open codec.\n");
		return -1;
	}
 
	/*
	* 在此处添加输出视频信息的代码
	* 取自于pFormatCtx，使用fprintf()
	*/
	FILE *fp = fopen("info.txt", "wb+");
	fprintf(fp,"时长：%d\n",pFormatCtx->duration);
	fprintf(fp,"封装格式：%s\n",pFormatCtx->iformat->long_name);
	fprintf(fp,"宽高：%d*%d\n",pFormatCtx->streams[videoindex]->codec->width, pFormatCtx->streams[videoindex]->codec->height);
 
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	//Output Info-----------------------------
	printf("--------------- File Information ----------------\n");
	av_dump_format(pFormatCtx, 0, filepath, 0);
	printf("-------------------------------------------------\n");
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
 
	int frame_cnt=0;
	while (av_read_frame(pFormatCtx, packet) >= 0) {//读取一帧压缩数据
		if (packet->stream_index == videoindex) {
			/*
			* 在此处添加输出H264码流的代码
			* 取自于packet，使用fwrite()
			*/
			fwrite(packet->data, 1, packet->size, fp_h264); //把H264数据写入fp_h264文件
 
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);//解码一帧压缩数据
			if (ret < 0) {
				printf("Decode Error.\n");
				return -1;
			}
			if (got_picture) {
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
					pFrameYUV->data, pFrameYUV->linesize);
 
				y_size = pCodecCtx->width*pCodecCtx->height;
				/*
				* 在此处添加输出YUV的代码
				* 取自于pFrameYUV，使用fwrite()
				*/
				printf("Decoded frame index: %d\n", frame_cnt);
 
				fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);    //Y 
				fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);  //U
				fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);  //V
 
				frame_cnt++;
 
			}
		}
		av_free_packet(packet);
	}
 
	//flush decoder
	//FIX: Flush Frames remained in Codec
	int frame_cnt1 = 0;
	while (1) {
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (ret < 0)
			break;
		if (!got_picture)
			break;
		sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
			pFrameYUV->data, pFrameYUV->linesize);
 
		int y_size = pCodecCtx->width*pCodecCtx->height;
		printf("Flush Decoder: %d\n", frame_cnt1);
		fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);    //Y 
		fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);  //U
		fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);  //V
		frame_cnt1++;
	}
	
	sws_freeContext(img_convert_ctx);
 
	//关闭文件以及释放内存
	fclose(fp_yuv);
	fclose(fp_h264);
 
	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
 
	return 0;
}
