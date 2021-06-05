/*************************************************************************
  @File Name: mainc.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 11时07分08秒
 ************************************************************************/

#include <stdio.h>

extern void test();

int main(int argc, char* argv[])
{

	test();
	printf("mainc test\n");
    
	extern int a;
	extern int b;
	a = 3;
	b = 4;
	printf("mainc a = %d, b = %d\n",a,b);

	return 0;
}
