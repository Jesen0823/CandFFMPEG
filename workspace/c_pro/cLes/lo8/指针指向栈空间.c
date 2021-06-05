/*************************************************************************
  @File Name: 指针指向栈空间.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 19时54分57秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

struct Student{
	int score;
	char name[20];
	int cass;
};

int main(int argc, char* argv[])
{

	struct Student *p;
	struct Student tmp;
	p= &tmp;
	p->score = 60;
	strcpy(p->name, "Jo");
	p-> cass = 1;
	printf("%d, %s , %d\n",p->score, p->name, p->cass);
     
	return 0;
}
