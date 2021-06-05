/*************************************************************************
  @File Name: 结构体嵌套.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 18时13分40秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

struct Info{
	int score;
	char address[50];
};

struct Student{
	char name[20];
	int id;
	struct Info info;
};

int main(int argc, char* argv[])
{
	struct Student s;
	s.info.score = 90;
	strcpy(s.info.address, "zhenjiang road 105.");
	strcpy(s.name, "Benjamen");
	s.id = 2;

	struct Student *p = &s;
	p->info.score = 92;
	printf("student name is %s,id is %d, his home address is %s and get %d in this Mathes test.\n", p->name, p->id, p->info.address, p->info.score );


	struct Student tmp = {"zhangtu", 3, 80, "hangzhou.xixi"};
	printf("student name is %s,id is %d, his home address is %s and get %d in Mathes test.\n", tmp.name, tmp.id, tmp.info.address, tmp.info.score );
     return 0;
}
