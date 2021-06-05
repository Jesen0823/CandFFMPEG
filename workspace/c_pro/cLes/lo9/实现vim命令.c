/*************************************************************************
  @File Name: 实现vim命令.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 15时55分21秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

/* 实现 vim 新建文件并编辑 的命令
 *
 * */

int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("param is error!\n");
		return -1;
	}

	// 写方式打开文件
	FILE *fp = fopen(argv[1], "w");
	// 从键盘读取fgets(),放在字符数组
	// 字符数组往文件逐个字符写入
	char buf[1024];
	while(1){
		// fgets()默认遇到换行符，结束读取
		fgets(buf, sizeof(buf), stdin);
		// 如果用户输入为":wq"，结束，保存文件
		if(strncmp(buf, ":wq", 3) == 0){
			break;
		}

		int i = 0;
		/*
		// 读取内容没有到结束符，则将读取写入文件
		while(buf[i] != '\0'){
			fputc(buf[i], fp);
			i++;
		}
		*/

		// 方法2：
		int n = strlen(buf);
		for(i = 0; i < n; i++){
			fputc(buf[i], fp);
		}
	}
	// 关闭文件
	fclose(fp);

    return 0;
}
