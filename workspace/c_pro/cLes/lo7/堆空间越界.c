/*************************************************************************
  @File Name: 堆空间越界.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 16时09分17秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	char *p = NULL;
	p = (char*) malloc(0); //err
	if(p == NULL){
		printf("分配失败\n");
		return 0 ;
	}
	strcpy(p,"nima");
	printf("%s\n",p);
	free(p);

    return 0;
}
