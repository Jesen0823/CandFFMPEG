/*************************************************************************
  @File Name: test2.cpp
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月05日 星期三 19时03分01秒
 ************************************************************************/

//#include <iostream>
#include <stdio.h>

struct Test{
	// 类中声明，类外面定义函数
	int a;

	void setA();

	int getA();

	static void fun(){
		printf("static fun...\n");
	}
};

// 加上作用域，告诉编译器setA属于struct Test,需要两个冒号
void Test::setA(){
	a = 10;
}

int Test::getA(){
	return a;
}

int main(int argc, char *argv[]){

	Test obj;
	obj.setA();
	int temp = obj.getA();
	printf("temp = %d\n", temp);

	// 静态方法，可以通过类名调用也可以通过对象调用
	Test::fun();
	obj.fun();
    return 0;
}
