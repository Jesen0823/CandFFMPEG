/*************************************************************************
  @File Name: 文件版排序问题补充.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 17时57分24秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

void write_file(){
	FILE *fp = NULL;
	fp = fopen("501.txt", "w");
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
	fp = fopen("501.txt", "r");
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

	// 排序
	int tmp;
	int j;
	for(i=0; i<n-1;i++){
		for(j=0; j<n-1-j; j++){
			if(a[j] > a[j+1]){
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	
	char dst[4*1024] = {0};
	char src[512];
	for(i = 0; i< n; i++){
		sprintf(src, "%d\n", a[i]); // 格式化为字符串
		strcat(dst, src);
	}

	// 关闭文件，重新写入排序后的数据
	fclose(fp);
	fp = NULL;
	fp = fopen("501.txt", "w");
	fputs(dst, fp);

	fclose(fp);
	fp = NULL;
	
}

int main(int argc, char* argv[])
{
	write_file();
	read_file();

     return 0;
}
