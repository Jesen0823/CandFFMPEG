/*************************************************************************
  @File Name: 文件四则运算.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 18时17分50秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int calc(int a, int b, char ch){
	switch(ch){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			return 0;
	}
	return 0;
}

void write_file(){
	FILE *fp =fopen("09.txt", "w");

	// 写文件
	fputs("10+1=\n", fp);
	fputs("10-1=\n", fp);
	fputs("10*1=\n", fp);
	fputs("10/1=\n", fp);
	fputs("10+2=\n", fp);
	fputs("10-2=\n", fp);
	fputs("10*2=\n", fp);
	fputs("10/2=\n", fp);
	//fputs("10/2=", fp); // 最后一个有换行没换行不一样

	fclose(fp);
	fp = NULL;
}

void read_file(){
	
	FILE *fp =fopen("09.txt", "r");
	
	// 读文件
	char buf[100];
	char tmp[1024*4] = {0}; // 定义并清空
	while(1){
		memset(buf, 0, sizeof(buf));

		fgets(buf, sizeof(buf), fp);
		// 为了解决最后一行有\n导致多打印一行内容，判断buf大小
		if(strlen(buf) > 0){
			printf("buf=%s\n", buf);
			// 提取a,b,运算符ch
			int a,b;
			char ch;
			sscanf(buf,"%d%c%d=\n", &a, &ch, &b);
			// 打印运算结果
			//printf("%d%c%d=%d\n", a,ch, b, calc(a,b,ch));
			
			// 格式化字符串到buf
			sprintf(buf, "%d%c%d=%d\n" , a, ch, b, calc(a, b, ch));
			strcat(tmp, buf);
		}else{
			printf("buf size :%ld\n", strlen(buf));
		}

		if(feof(fp)){
			break;
		}
	}
	printf("%s", tmp);

	// 关闭文件重新以w打开文件，以便清空文件
	fclose(fp); 
	fp = fopen("09.txt", "w");
	// 写入tmp
	fputs(tmp, fp);


	fclose(fp);
	fp = NULL;
}

int main(int argc, char* argv[])
{

	write_file();
	read_file();

     return 0;
}
