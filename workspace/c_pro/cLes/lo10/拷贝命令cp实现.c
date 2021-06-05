/*************************************************************************
  @File Name: 拷贝命令cp实现.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月02日 星期日 00时03分27秒
 ************************************************************************/

#include <stdio.h>
/*读多少写多少
 * len = fread(buf,1, sizeof(buf), srcFp);
 * fwrite(buf, 1, len, dstFp);
 *
 * */

int main(int argc, char* argv[])
{
	if(argc != 3){
		printf("params is error.\n");
		return -1;
	}
	
	FILE *srcFp = NULL;
	FILE *dstFp = NULL;

	// 1.打开源文件
	srcFp = fopen(argv[1], "r");
	// 2.打开目的文件
	dstFp = fopen(argv[2], "w");
	if(srcFp == NULL || dstFp == NULL){
		printf("open file error.\n");
		return -1;
	}

	// 3.循环读取源文件，写入目的文件
	char buf[4*1024];
	int len;
	while(1){
		len = fread(buf, 1, sizeof(buf), srcFp);
		printf("len = %d\n", len);
		if(len ==0){
			break;
		}
		fwrite(buf, 1, len, dstFp);
	}

	// 4.关闭文件
	fclose(srcFp);
	fclose(dstFp);
	srcFp = NULL;
	dstFp = NULL;

    return 0;
}
