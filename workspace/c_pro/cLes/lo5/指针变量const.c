/*************************************************************************
  @File Name: 指针变量const.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 10时49分01秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
	
	int a = 10;
	const int *p2 = &a;
 	*p2 = 11; //Error
	// const修饰*，代表指针指向的内存是只读
	p2 = NULL; 

	return 0;
}
