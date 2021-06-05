/*************************************************************************
  @File Name: 指针指向数组.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 11时29分22秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

	int a[] = {1,2,3,4,5,6,7};
	int *p = NULL;
	// p指针指向首元素
	p = &a[0]; // 等价 p = a;

	int i = 0;
	for(i = 0; i < 7; i++){ // 3种打印等价
		printf(" a[i] = %d ",a[i]);
		printf(",p+i  = %d ", *(p+i));
		printf(",p[i] = %d\n ", p[i]);
	}

	for(i = 0; i < 7; i++){
		printf("p++, %d\n, ", *p);
		p++;
	}
	
	return 0;
}
