/*************************************************************************
  @File Name: 文件打开关闭.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 18时30分12秒
 ************************************************************************/

#include <stdio.h>

/* 1. fopen在堆区分配空间，返回堆区地址给fp
 * 2. FILE 结构体成员保存文件的信息
 * 3. "w"如果文件不存在就新建，存在则清空并打开
 *	  "r"如果文件不存在打开失败
 *	  "a"如果不存在则新建且广播自动放在文件末尾
 * */

int main(int argc, char* argv[])
{
	FILE *fp = NULL;
	fp = fopen("./02.txt", "w");
	// 等价操作1：
	//char *p = "./02.txt";
	//fp = fopen(p, "w");
	
	// 等价操作2：
	//char *mode = "w";
	//fp = fopen("./02.txt", mode);
	
	// 等价操作3:
	//char p[] = "./02.txt";
	//fp = fopen(p, "w");

	if(fp == NULL){
		printf("file 01 open failed.\n");
		perror("fopen 01");
		return -1;
	}

	fclose(fp);
	fp = NULL;


    return 0;
}
