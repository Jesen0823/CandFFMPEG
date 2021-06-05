/*************************************************************************
  @File Name: 字符串比较.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 11时31分14秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argv, char* argc[]){
	// 字符串比较，是比较每一个字符的ASCII码 如：abc>Abcd
	char str[] = "abc";
        char str2[] = "Abcd";
	char str3[] = "world";

	int flag = strcmp(str, str2);
	if(flag > 0){
		printf("%s > %s\n",str,str2);
	}else{
		printf("%s > %s\n",str2,str);
	}

	// 比较前两个字符
	int flag2 = strncmp(str, str3, 2);
	printf("flag2 is :%d\n", flag2);	

	return 0;
}
