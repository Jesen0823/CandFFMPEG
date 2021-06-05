/*************************************************************************
  @File Name: 结构体套一级指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 20时22分08秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	int score;
	char name[20];
	int class;
	char *address;
	int height;
};

int main(int argc, char* argv[])
{

	struct Student s;
	s.score = 76;
	strcpy(s.name, "jesen");
	s.class = 1;

	// 导致段错误 Error!:
	//strcpy(s.address, "guangdong");
	
	// 修复方案1：
	//s.address = "guangdong";
	
	// 修复方案2：
	/*
	char buf[100];
	s.address = buf; // 拥有指向空间
	strcpy(s.address, "guangdong");
	printf("buf = %s\n", buf);
	*/

	// 修复方案3：
	s.address = (char *)malloc((strlen("guangdong") + 1) * sizeof(char));
	strcpy(s.address, "guangdong");

	s.height = 170;
	printf("s.name =%s, s.score =%d, s.class =%d, s.address=%s\n", s.name, s.score, s.class, s.address);

	free(s.address);
    return 0;
}
