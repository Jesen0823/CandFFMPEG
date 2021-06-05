/*************************************************************************
  @File Name: cat命令实现.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 13时21分02秒
 ************************************************************************/

#include <stdio.h>

/*利用which cat找到cat路径，将该文件执行的可执行程序放到cat目录
 * 则可以使用该文件命令作为工具使用
 *
 * */
int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("请输入文件！\n");
	}
	FILE *fp = fopen(argv[1], "r");

	char ch;
	while(1){
		ch = fgetc(fp);
		if(feof(fp)){
			break;
		}
		printf("%c", ch);
	}

	fclose(fp);

     return 0;
}
