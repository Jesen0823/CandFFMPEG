/*************************************************************************
  @File Name: 字符串追加.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 12时00分03秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argv, char* argc[]){
	char src[] = "Peek";
	char dst[100] = "abc";
	strcat(dst,src); // 追加
	printf("dst = %s\n", dst);
	strncat(dst,src, 2); // 指定长度追加
	printf("dst = %s\n", dst);

	return 0;
}
