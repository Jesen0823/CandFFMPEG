/*************************************************************************
  @File Name: 字符串读fgets.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 16时50分03秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void line_read(FILE *fp){
	
	// 从fp关联的文件读取放入buf, 一次最大读取量为sizeof(buf) -1
	// 遇到换行符，文件结尾，出错，结束读取
	char buf[100];
	fgets(buf, sizeof(buf), fp);
	printf("buf1 = %s\n", buf);
	fgets(buf, sizeof(buf), fp);
	printf("buf2 = %s\n", buf);
	fgets(buf, sizeof(buf), fp);
	printf("buf3 = %s\n", buf);
	fgets(buf, sizeof(buf), fp);
	printf("buf4 = %s\n", buf);
	fgets(buf, sizeof(buf), fp);
	printf("buf5 = %s\n", buf);
	fgets(buf, sizeof(buf), fp);
	// 读取到文件末尾不再读取，打印的buf是上次缓存的内容
	// 除非加memset(buf, 0, sizeof(buf))清空buf
	//memset(buf, 0, sizeof(buf));
	printf("buf6 = %s\n", buf);
}

int main(int argc, char* argv[])
{
	FILE *fp = NULL;
	fp = fopen("08.txt", "r");
	if(fp == NULL){
		return -1;
	}

	// 一个个读取
	line_read(fp);
	
	//如何全部读取？
	fp = fopen("08.txt", "r");
	char buf[100];
	while(1){
		fgets(buf, sizeof(buf), fp);
		if(feof(fp)){
			break;
		}
		printf("bufAll = %s", buf);
	}

	fclose(fp);

     return 0;
}
