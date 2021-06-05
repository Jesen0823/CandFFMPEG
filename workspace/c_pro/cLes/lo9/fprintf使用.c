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

	FILE *fp = fopen("10.txt", "w");

	int i = 0;
	int num;
	// 设置随机种子
	srand((unsigned int)time(NULL));
	for(i=0; i<10; i++){
		num = rand() % 100;
		// 将字符串显示在屏幕
		printf("%d\n", num);
		//类似
		fprintf(stdout, "%d\n", num);
		// 将字符串写入fp关联的文件
		fprintf(fp, "%d\n", num);
	}

	fclose(fp);
	fp = NULL;

    return 0;
}
