/*************************************************************************
  @File Name: 字符串切割.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 14时12分10秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argv, char* argc[]){

	char buf[] = "abc,took,909,cn";

	/*
	 *1.strtok() 会破坏原来的数据结构
	  切割符号会换成结束符\0
	  可以copy一份，操作副本
	  2.strtok()第二次调用时，第一个参数需要写NULL
	 * */
	char temp[100];
	strcpy(temp, buf);

	char *ret = strtok(temp, ",");
	printf("ret = %s\n", ret);
	printf("temp = %s\n", temp);
	printf("buf = %s\n", buf);

	// 第二次调用
	ret = strtok(NULL, ",");
	printf("ret2 = %s\n", ret);

	// 优化
	char *p;
	char tmp[100];
	strcpy(tmp, buf);
	p = strtok(tmp, ",");
	while(p != NULL){
		printf("p = %s\n", p);
		p = strtok(NULL, ",");
	}


	return 0;
}
