/*************************************************************************
  @File Name: 局部变量的地址.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 16时00分21秒
 ************************************************************************/

#include <stdio.h>

int *fun(){

	int a = 0;
	return &a;
}

int main(int argc, char* argv[])
{

	int *p = NULL;
	p = fun(); // fun操作完了a的存储空间会释放,p最终接收了一个野指针
	*p = 110;
	printf("result is :%d\n",*p);

	return 0;
}
