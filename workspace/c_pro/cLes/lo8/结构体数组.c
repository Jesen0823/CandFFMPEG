/*************************************************************************
  @File Name: 结构体数组.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 17时48分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

struct Student{
	char name[20];
	int score;
	int class;
};

int main(int argc, char* argv[])
{
	struct Student s;
	struct Student a[5];// 结构体数组
	// 多种操作结构体的方法：
	strcpy(a[0].name, "qiuji");
	a[0].score = 70;
	a[0].class = 4;

	strcpy((a+1)->name, "qiuji2");
	(a+1)->score = 71;
	(a+1)->class = 3;

	strcpy((*(a+2)).name, "qiuji3");
	(*(a+2)).score = 80;
	(*(a+2)).class = 4;
	
	struct Student *p = a;
	p = &a[0];
	strcpy(p[3].name, "qiuji4");
    p[3].score = 70;
    p[3].class = 4;

	(p+4)->score = 77;
	strcpy((p+4)->name, "qiuji5");
	(p+4)->class = 1;

	int i= 0;
	int n = sizeof(a) / sizeof(a[0]);
	for(i = 0; i < n; i++){
		printf("%s, %d, %d\n", p[i].name, p[i].score, p[i].class);
	}


	return 0;
}
