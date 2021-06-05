/*************************************************************************
  @File Name: 字符串.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月26日 星期一 23时51分43秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

/* 1.C语言没有字符串，用字符数组模拟
 * 2.字符串一定是字符数组，字符数组不一定是字符串
 * 3.若字符数组以字符'\0'结尾，则一定是字符串
 *
 * */
	char b[3] = {'a','A','c'}; // 字符数组
	char c[10] = {'a','A','c','\0'}; // 字符串
	char d[10] = {'a','A','c',0}; // 字符串

	/*字符数组初始化*/
	char a1[] = {'a','A','c'};
	printf("a1=%s\n"); // %s打印会乱码，因为没有结束符\0
	printf("d = %s\n",d);
	char a1s[] = "aAc"; // 4个字符，字符串隐藏一个0

	char a2[] = {'a','A','c','\0'};
	char a3[] = {'a','A','c','\0','s','p','\0'};
	printf("a2 = %s\n", a2);
	printf("a3 = %s\n", a3);
	
	char a4[10] = {'a','A','c'}; //后面自动赋值0
	printf("a4 = %s\n", a4);

	// 常用字符串初始化，结尾自动补0
	char a5[10] = "abc";
	char a6[] = "abc";
	printf("a5 = %s\n", a5);

	char a7[] = "\0abc";
	char a8[] = "\069abc"; // 0紧挨数字认作ASCII码
	printf("a7 = %s\n", a7);
	printf("a8 = %s\n", a8);
	printf("a7 = %s\n", a7);

	

	return 0;
}
