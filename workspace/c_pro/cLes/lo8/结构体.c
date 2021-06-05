/*************************************************************************
  @File Name: 结构体.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 17时04分31秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
// 结构体没有定义变量前不会分配内存空间
struct Student{
	char name[50];
	int score;
	int class;
};

int main(int argc, char* argv[])
{
	// 定义结构体变量
	struct Student stu;
	// 初始化
	// 只有在定义时才能初始化
	struct Student stu2 = {"jesen",99, 12};

	// 如果是普通变量，用.运算符
	// 如果是指针变量，用->
	stu.score = 88; //等价 (&stu)->score = 88;
	//stu.name = "kotli";// Error
	strcpy(stu.name, "Kotli");
	stu.class = 12;

	struct Student *stu3; //如果是指针，需要有合法指向
	stu3 = &stu;
	stu3->score = 80;
	strcpy(stu3->name, "Jahe");
	stu3->class = 11; // 等价 (*stu3).class = 11;
	


    return 0;
}
