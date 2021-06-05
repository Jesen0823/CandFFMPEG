/*************************************************************************
  @File Name: const修饰字符指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 17时26分38秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	char buf[] = "foodou";
	char *p1 = buf;
	*p1 = 'a';

	//const修饰表示指针指向的内存不可修改
	const char *p2 = buf;
	*p2 = 'b'; // error

     return 0;
}
