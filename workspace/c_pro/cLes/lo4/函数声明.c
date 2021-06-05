/*************************************************************************
  @File Name: 函数声明.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 15时34分51秒
 ************************************************************************/

#include <stdio.h>

// 可以声明多次，只要在调用前声明就行
// extern可以省略，形参名可以不一样,变量名也可以不写只写int
// 函数在main函数之后放置，一定要声明才能调用
extern int testFun(int a);
int testFun(int x);


int main(int argv, char* argc[]){
	extern int testFun(int r);

	int rult =  testFun(8);
	printf("转换结果：%d\n", rult);
	return 0;
}

int testFun(int x){
	return x > 10 ? x : 10;
}
