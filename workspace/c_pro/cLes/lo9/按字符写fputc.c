/*************************************************************************
  @File Name: 按字符写fputc.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 20时41分51秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	//1.打开文件
	FILE *fp = NULL;
	fp = fopen("03.txt", "w");
	if(fp == NULL){
		perror("fopen");
		return -1;
	}

	//2.写文件fputc,一次只能写一个字符,光标自动后移
	fputc('a', fp);
	fputc('p', fp);
	
	char ch = 'a';
	while(ch <= 'z'){
		fputc(ch, fp);
		ch++;
	}

	char buf[] = "android studio";
	int i = 0;
	int n = strlen(buf);
	for(i=0; i < n; i++){
		fputc('\n', fp); // 输入一个换行符
		fputc(buf[i], fp);
	}

	fputc(1, fp);
	fputc(-2, fp);
	fputc(97,fp);

	// 补充,写入到标准输出设备屏幕
	fputc('A', stdout);
	fputc('B', stdout);

	//3.关闭文件
	fclose(fp);

     return 0;
}
