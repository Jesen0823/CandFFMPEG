/*************************************************************************
  @File Name: 多级指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 21时35分04秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

	// 需要保存变量地址的基础上加一个*
	int a = 10;
	int *p = &a;
	int **q = &p;
	int ***t = &q;
	int ****m = &t;

	*m;    // t
	**m;   // q
	****m; //a
	printf("%d\n", ****m);


	return 0;
}
