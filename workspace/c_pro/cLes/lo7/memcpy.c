/*************************************************************************
  @File Name: memcpy.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 14时27分05秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char p[] = "hello\0mike";
	char buf[100];
	strncpy(buf, p, sizeof(p));
	printf("buf = %s\n", buf);
	printf("buf end = %s\n", buf + strlen("hello") +1);

	memset(buf, 0, sizeof(buf)); // 先清空数组
	memcpy(buf, p, sizeof(p));
	printf("buf 2 = %s\n", buf);
	printf("buf 2 end = %s\n", buf + strlen("hello") +1);

	int src[] = {1,2,3,4,5,6};
	int dst[10];
	memcpy(dst, src, sizeof(src));
	int i;
	for(i = 0; i < 6; i++){
		printf("dst %d\n", dst[i]);
	}

	// 使用memcpy要防止出现内存重叠,如果重叠要用memmove()
	memcpy(&src[2], src, 4*sizeof(int));

	int n = sizeof(src) / sizeof(src[0]);
	for(i = 0; i < n; i++){
		printf("src 重叠  %d\n", src[i]);
	}
	memmove(&src[2], src, 4*sizeof(int));

	for(i = 0; i < n; i++){
		printf("src move %d\n", src[i]);
	}


	return 0;
}
