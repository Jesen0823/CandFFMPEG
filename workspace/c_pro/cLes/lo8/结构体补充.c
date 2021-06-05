/*************************************************************************
  @File Name: 结构体补充.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 17时27分32秒
 ************************************************************************/

#include <stdio.h>

// 不常用
struct Student{
	char name[20];
	int score;
	int class;
}s1 = {"Jol",40,6} ,s2;

// 匿名结构体，不常用
struct {
	char name[20];
	int score;
	int class;
}s3,s4;

int main(int argc, char* argv[])
{
	printf("%s, %d, %d\n", s1.name, s1.score, s1.class);
     return 0;
}
