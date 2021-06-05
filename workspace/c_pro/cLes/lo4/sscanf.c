/*************************************************************************
  @File Name: sscanf.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 13时20分26秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

	int a, b, c;
	printf("输入a,b,c:");
	scanf("%d %d %d",&a,&b,&c);
	printf("a = %d, b= %d, c= %d\n",a,b,c);

	// 从buf中以指定格式提取内容
	char buf[] = "1 2 3";
	int a1, a2, a3;
	sscanf(buf, "%d %d %d", &a1, &a2, &a3);
	printf("a1 = %d, a2 = %d, a3 = %d\n", a1, a2, a3);

	// 提取整型变量最方便·
	// 提取字符串要格式一致，用空格或者正则提取，不能以特殊字符或标点符号提取
	char str[] = "a1=1, a2=2, a3=3";
	a1 = 0;
	a2 = 0;
	a3 = 0;
	sscanf(str, "a1=%d, a2=%d, a3=%d", &a1, &a2, &a3);
	printf("a1 = %d, a2 = %d, a3 = %d\n", a1, a2, a3);

	return 0;
}
