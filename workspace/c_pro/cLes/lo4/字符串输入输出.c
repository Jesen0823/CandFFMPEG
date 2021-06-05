/*************************************************************************
  @File Name: 字符串输入输出.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 00时30分38秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
	
	char a[20];
	printf("输入a:\n");
	scanf("%s",a); // 数组是首地址，不用&;只会取第一个空格前面的内容
	printf("a = %s\n",a);
	
	/*
	 *scanf()的缺陷：不做越界检查
	 * */
	char b[5];
	printf("输入b:\n");
	scanf("%s",b); // 输入"abcdefg",有的编译器检测不出
	printf("b = %s\n",b);

	char buf[10];
	// gets()可以从键盘读取字符串，放在指定数组
	// 允许空格，但也不做越界检查
	gets(buf);
	printf("gets buf=%s",buf);
	// puts()把buf输出到屏幕，屏幕上会换行，字符串本身不会多换行
        puts(buf);                                                             
        printf("gets puts buf %s", buf);


	char buf2[10];
	//stdin表示从标准输入，即键盘读取内容
	//读取内容放入指定buf,读取长度不会超出sizeof(buf) -1 ,
	//会读取换行
	fgets(buf2, sizeof(buf2), stdin);
	printf("get buf2=%s", buf2);

	// 把buf输出到屏幕，屏幕上会换行，字符串本身不会多换行
	fputs(buf2);
	printf("getput buf2=%s", buf2);

	return 0;
}
