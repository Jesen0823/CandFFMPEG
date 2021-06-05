/*************************************************************************
  @File Name: 结构体套一级指针2.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 22时11分10秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	int score;
	char name[20];
	int class;
	char *address;
};


int main(int argc, char* argv[])
{
	struct Student *p;
	// 需要给p分配空间
	p = (struct Student*)malloc(sizeof(struct Student));
	if(p == NULL){
		printf("分配堆失败\n");
		return -1;
	}

	
	p->score = 60;
	strcpy(p->name, "Li");
	p->class = 2;
	p->address = (char *)malloc(sizeof(char)*(strlen("xihu")+1));

	strcpy(p->address, "xihu"); // 段错误 Error,需要给p分配空间

	printf("score=%d, address= %s\n", p->score, p->address);	
	
	if(p->address != NULL){
		free(p->address);
		p->address = NULL;
	}
	if(p != NULL){
		free(p);
		p = NULL;
	}

	return 0;
}
