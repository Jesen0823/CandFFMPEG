/*************************************************************************
  @File Name: 指针指向栈区空间.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 15时08分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	int *p;
	
	// 分配int大小的堆区空间
	//1. 返回堆区首元素地址(void *)，失败返回NULL
	//2. 动态分配的空间，如果出现没有结束不会自动释放，需要人为释放
	// free(p);不是释放p变量，是释放p指向的内存
	//3. 同一块堆区内存只能释放一次
	//4. 释放不是指内存消失，是指该块内存系统回收用户无法继续使用
	// 如果释放后继续操作该内存会发生野指针
	p =(int *)malloc(sizeof(int));
	if(p == NULL){
		printf("分配失败");
		return -1;
	}
	*p = 10;
	printf("*p = %d\n", *p);
	
	if(NULL != p){ // 防止重复free
		free(p);
		p = NULL;
	}


    return 0;
}
