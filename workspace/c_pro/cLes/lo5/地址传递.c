/*************************************************************************
  @File Name: 地址传递.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 15时04分12秒
 ************************************************************************/

#include <stdio.h>

void swap(int *m, int *n){
	int temp;
	temp = *m;
	*m = *n;
	*n = temp;
}

int main(int argc, char* argv[])
{
	int a = 11;
	int b = 22;

	// 值传递，不管变量是什么类型，变量本身传递
	//swap(a,b);
	//地址传递
	//通过函数改变实参，必须用地址传递
	swap(&a, &b);
	printf("a=%d, b=%d\n",a,b);

	return 0;
}
