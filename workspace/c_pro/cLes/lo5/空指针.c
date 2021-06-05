/*************************************************************************
  @File Name: 空指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 21时23分19秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
	
	// 空指针是指针变量值为0
	int *p = NULL;

	int a = 11;
	p =&a;

	if(p != NULL){
		*p = 100;
	}

	return 0;
}
