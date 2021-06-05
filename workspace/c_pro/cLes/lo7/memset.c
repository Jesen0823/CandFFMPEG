/*************************************************************************
  @File Name: memset.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 14时17分07秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int a;
	// 第二个参数，整型，按字符处理
	memset(&a, 0, sizeof(a));
	printf("a = %d\n",a);

	int b[10];
	memset(b,0, sizeof(b)); // 清空数组，数组清0

	char str[10];  // 处理字符数组
	memset(str, 'A', sizeof(str));


     return 0;
}
