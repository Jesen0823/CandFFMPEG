/*************************************************************************
  @File Name: 栈越界.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 14时05分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// 命令：$ ulimit -a

int main(int argc, char* argv[])
{

	// 要在栈区分配很大的内存，越界导致段错误
	int a[10000000000] = {0};

	int *p = (int *)malloc(100000000*sizeof(int));
	if(p == NULL){
		printf("分配失败");
	}
     return 0;
}
