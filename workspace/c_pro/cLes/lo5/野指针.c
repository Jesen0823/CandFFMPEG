/*************************************************************************
  @File Name: 野指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 18时03分21秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

	// 野指针：指针变量保存了一个没有意义的地址，非法的地址
	int *p = 0x2230;

	// 操作野指针本身没有问题
	printf("p = %d\n", p);
	
	// 操作野指针指向的内存就会有问题
	*p = 100;

	return 0;
}
