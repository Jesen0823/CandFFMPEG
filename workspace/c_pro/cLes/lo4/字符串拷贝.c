/*************************************************************************
  @File Name: 字符串拷贝.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 10时36分23秒
 ************************************************************************/

#include <stdio.h>
#include <string.h> // strcpy() strncpy()

int main(int argv, char* argc[]){
	
	char src[100] = "Just do it";
	char dst[100] = "";
	// 拷贝数组的内容
	strcpy(dst,src);
	printf("dst = %s\n",dst);
	printf("src = %s\n",src);
	
	char src2[100] = "Just do\0 it";
        char dst2[100] = "a";
        // 拷贝数组的内容,遇到/0结束
        strcpy(dst2,src2);
        printf("dst2 = %s\n",dst2);
        printf("src2 = %s\n",src2);

	char src3[100] = "Just do it";
        char dst3[100] = "aaa";
        // 拷贝数组的内容,遇到/0结束
        strncpy(dst3,src3, strlen(src3));
	//strncpy(sdt3, src3, strlen(src3)+1);
        printf("dst3 = %s\n",dst3);
        printf("src3 = %s\n",src3);

	
	return 0;
}
