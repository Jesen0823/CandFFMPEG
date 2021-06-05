/*************************************************************************
  @File Name: 字符串长度.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 10时22分36秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argv, char* argc[]){
	char buf[] = "Kotlin";
	// 从首元素到结束符长度，\0不算
	// sizeof(buf)算\0的长度
	int len = strlen(buf);
	printf("1. %s length is %d\n", buf, len);
	printf("1. %s sizeof is %ld\n", buf, sizeof(buf));

	char buf2[] = "\0Kotlin";
	// 从首元素到结束符长度，\0不算
	int len2 = strlen(buf2);
	printf("2.  %s length is %d\n", buf2, len2);
	printf("2.  %s sizeof is %ld\n", buf2, sizeof(buf2));
	return 0;
}
