/*************************************************************************
  @File Name: test.cpp
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月04日 星期二 22时19分13秒
 ************************************************************************/
/*
 * gcc test.cpp -lstdc++
 * */
#include <stdio.h>
//#include <iostream>

struct Test{
	int a;

	void setA(int x){
		a = x;
	}

	int getA(){
		return a;
	}
};

int main(int argc, char *argv[]){

	// c++中叫做类的对象
	Test obj;
	obj.setA(10);
	int oA = obj.getA();
	printf("oA = %d\n", oA);

	Test *p = &obj;
	int m = p->getA();
	printf("m = %d\n", m);

    return 0;
}
