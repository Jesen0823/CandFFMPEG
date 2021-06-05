/*************************************************************************
  @File Name: 万能指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 10时24分01秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

	// void *指针也叫万能指针，可以指向任何类型变量
	void *p = NULL;
	int a = 10;
	p = &a;
	// *p = 100; //需要转换类型
	* ((int *)p) = 100;
	printf("*p = %d\n", * ((int *)p));

	
	return 0;
}
