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
	fp = fopen("04.txt", "w");
	if(fp == NULL){
		perror("write_file fopen");
		return;
	}

	char *p = "I'm not hungury at all";
	int i = 0;
	int n = strlen(p);

	for(i = 0; i < n; i++){
		fputc(p[i], fp);
	}
	fclose(fp);
}


void read_file(){

	FILE *fp = NULL;
	fp = fopen("04.txt", "r");
	if(fp == NULL){
		perror("read_file fopen");
		return;
	}

	// 读文件，每次读一个字符,光标自动后移
	char ch;
	while(1){
		ch = fgetc(fp);
		printf("%c",ch);

		if(ch == -1){ // 文本结束符,宏定义EOF
			// 等价 ch == EOF
			break;
		}
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
    return 0;
}
