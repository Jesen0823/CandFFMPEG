/*************************************************************************
  @File Name: 局部变量.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 10时09分05秒
 ************************************************************************/

#include <stdio.h>

/*局部变量只在{}内有效，执行到使用语句才分配空间
 *如果不初始化默认值为随机数
 * */

/*静态局部变量也只在{}有效，但是编译阶段就已经分配空间，函数调用时候已经存在了
 *离开{},静态变量不会释放，直到程序结束。
  如果局部static不初始化值默认为0，且只能用常量初始化
 * 初始化只能执行一次，可以多次赋值
 * */

// 静态变量存在data区
void fun(){
	int i = 0;
	i++;
	printf("i = %d\n",i);
}

void static_fun(){
	static int i = 0;
	i++;
	printf("static i = %d\n",i);
}

int main(int argc, char* argv[])
{
	fun();
	fun();
	static_fun();
	static_fun();

    return 0;
}
