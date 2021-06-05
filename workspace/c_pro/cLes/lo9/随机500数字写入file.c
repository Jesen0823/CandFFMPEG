/*************************************************************************
  @File Name: 随机500数字写入file.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 17时57分24秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 500

void write_file(){
	FILE *fp = NULL;
	fp = fopen("500.txt", "w");
	if(fp == NULL){
		perror("write_file fopen");
		return;
	}
	// 设置种子
	srand((unsigned int)time(NULL));

	int i;
	int num;
	char buf[100];
	for(i = 0; i< MAX; i++){
		num = rand() % 100; // 随机数在100以内
		// 格式化字符串
		sprintf(buf, "%d\n", num);
		// 写入文件
		fputs(buf, fp);
	}
	fclose(fp);
	fp = NULL;
}

void read_file(){
	FILE *fp = NULL;
	fp = fopen("500.txt", "r");
	if(fp == NULL){
		perror("read_file fopen");
		return;
	}
	int a[1024];
	int i = 0;
	char buf[100];
	int num;

	while(1){
		fgets(buf, sizeof(buf), fp);
		if(feof(fp)){
			break;
		}
		sscanf(buf, "%d\n", &num);
		a[i] = num;
		i++;
	}
	int n = i;
	printf("num of number is tatal:%d\n",n);
	for(i = 0; i< n; i++){
		printf("%d, ",a[i]);
	}
	printf("\nEND\n");
}

int main(int argc, char* argv[])
{
	write_file();
	read_file();

     return 0;
}
