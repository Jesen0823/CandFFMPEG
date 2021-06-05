/*************************************************************************
  @File Name: sprintf.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 13时11分38秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
	
	int a = 10;
	char ch = 'd';
	char buf[] = "Yahoo";

	char dst[100];
	printf(dst, "a=%d,ch = %c, buf = %s\n", a, ch, buf);

	// 格式化一个字符串，输出到指定数组
	sprintf(dst, "a=%d,ch = %c, buf = %s\n", a, ch, buf);
	printf("@@%s@@",dst);

	return 0;
}
