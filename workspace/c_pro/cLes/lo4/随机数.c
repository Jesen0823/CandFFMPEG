/*************************************************************************
  @File Name: 随机数.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 00时34分48秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argv, char* argc[]){
	// 设置随机数种子，一次即可
	// srand参数一样，随机数一样
	srand(1000);

	int i = 0;
	for(i=0; i < 10; i++){
		printf("%d\n", rand());
	}
	
	srand((unsigned int)time(NULL)); // 入参不一样
	for(i=0; i < 10; i++){
		printf("time, %d\n", rand());
	}

	return 0;
}
