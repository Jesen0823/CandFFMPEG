/*************************************************************************
  @File Name: 指针指向栈区空间.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 15时08分43秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{

	int *p;
	int a;
	p = &a;
	*p = 10;
	printf("*p = %d\n", *p);

     return 0;
}
