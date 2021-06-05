/*************************************************************************
  @File Name: typedef.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 01时21分07秒
 ************************************************************************/

#include <stdio.h>


typedef struct Test{
	int a;
}Tst; //别名

int main(int argc, char* argv[])
{
	/* typedef 是给一个已存在类型取别名
	 * 不能创建新类型
	 * 与宏定义的区别：宏定义发生在预处理，typedef发生在编译阶段
	 * */
	typedef int int64;
	int64 a;


     return 0;
}
