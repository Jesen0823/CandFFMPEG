/*************************************************************************
  @File Name: fprintf使用.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 20时21分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{

	FILE *fp = fopen("10.txt", "r");

	int i = 0;
	int num;

	for(i=0; i<10; i++){
		fscanf(fp, "%d\n", &num);
		printf("read result = %d\n", num);
	}
	

	fclose(fp);
	fp = NULL;

    return 0;
}
