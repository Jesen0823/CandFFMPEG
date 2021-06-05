/*************************************************************************
  @File Name: 使用fflush.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月02日 星期日 12时21分52秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE *fp = fopen("03.txt", "w");

	fputs("this is Sunday", fp);
	// 数据在缓冲区
	// 默认情况缓冲区满时，自动刷新缓冲区
	// 文件正常关闭，缓冲区自动刷新
	// 文件不关闭程序没结束，缓冲区要实时刷新调用fflush
	fflush(fp);
	while(1){
		//fputs("You are my Sun", fp);
		NULL;		
	}

     return 0;
}
