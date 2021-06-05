/*************************************************************************
  @File Name: 字符串常量.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 20时24分22秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	// 每个字符串变量都是一个字符串首元素地址
	// 字符串常量放在data区的文字常量区,内容不可修改
	char *p1 = "google";
	printf("p1 = %p\n",p1);
	printf("p1 %c\n", *p1);
	printf("s1 = %s\n", "google");
	printf("s2 = %p\n", "google");
	printf("首元素：%c\n",*"google");
	printf("s3 = %p\n", "google"+1);
	printf("g = %p\n", "g");

    // 字符串拷贝
	char src[100] = "Just do it";
	char dst[100] = "";
	// 拷贝数组的内容
	strcpy(dst,src);
	printf("dst = %s\n",dst);
	printf("src = %s\n",src);

	// BUT:字符串常量拷贝[Error!]，字符串常量指向文字常量区不可修改
	printf("段错误：\n");
	char *p2 = "Just do it";
	strcpy(p2, "google");


	return 0;
}
