/*************************************************************************
  @File Name: 按字符读fgetc.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 21时00分52秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void write_file(){
	FILE *fp = NULL;
	fp = fopen("05.txt", "w");
	if(fp == NULL){
		perror("write_file fopen");
		return;
	}

	// 写二进制
	fputc('a', fp);
	fputc('p', fp);
	fputc('s', fp);
	fputc(-1, fp);
	fputc('l', fp);
	fputc(-2, fp);

	fclose(fp);
}


void read_file(){

	FILE *fp = NULL;
	fp = fopen("05.txt", "r");
	if(fp == NULL){
		perror("read_file fopen");
		return;
	}

	// 读文件，每次读一个字符
	char ch;
	while(1){
		ch = fgetc(fp);
	
		if(feof(fp)){ // 文件结束符
			break;
		}
		//printf("%c",ch);
		printf("%d",ch);
	}
	printf("\n");
	

	fclose(fp);
}

int main(int argc, char* argv[])
{
	// 写入文件
	write_file();

	read_file();
	// 如果是文本形式，可以通过-1(EOF)判断文件是否结尾
	// 如果是二进制文件，不能以-1判断结尾
	// feof()判断文件是否结尾，任何文件能够判断,文件结尾返回真
    return 0;
}
