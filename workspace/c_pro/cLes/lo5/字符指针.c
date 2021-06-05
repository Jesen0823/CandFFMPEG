/*************************************************************************
  @File Name: 字符指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 16时56分48秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	char str[] = "hello";
	str[0] = '1';
	*(str+1) = '2';
	printf("str = %s\n", str); // 12llo

	char *p = NULL;
	p = &str[0];
	p = str; // 数组名是首元素地址

	*p = 'a';
	p++;
	*p = 'b';
	printf("str = %s\n",str);//abllo
	printf("p = %s\n",p); //bllo
	printf("p-1 = %s\n",p-1); //abllo 

     return 0;
}
