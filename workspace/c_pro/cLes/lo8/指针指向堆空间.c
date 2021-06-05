/*************************************************************************
  @File Name: 指针指向栈空间.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 19时54分57秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	int score;
	char name[20];
	int cass;
};

int main(int argc, char* argv[])
{
	struct Student *p; 
	p =(struct Student *)malloc(sizeof(struct Student));
	
	if(p == NULL){
		printf("堆空间分配失败");
		return -1;
	}
	
	p->score = 60;
	strcpy(p->name, "Jo");
	p-> cass = 1;
	printf("%d, %s , %d\n",p->score, p->name, p->cass);
     
	if(NULL != p){
		free(p);
		p = NULL;
	}


	return 0;
}
