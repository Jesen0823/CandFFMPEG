/*************************************************************************
  @File Name: 全局变量的地址.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 16时00分21秒
 ************************************************************************/

#include <stdio.h>

// 全局变量，直到程序结束才释放
int a;

int *fun(){

	return &a;
}

int main(int argc, char* argv[])
{

	int *p = NULL;
	p = fun(); // 
	*p = 110;
	printf("result is :%d\n",*p);

	return 0;
}
