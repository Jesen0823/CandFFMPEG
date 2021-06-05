/*************************************************************************
  @File Name: 按字符串写fputs.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 16时26分12秒
 ************************************************************************/

#include <stdio.h>

void review(){
	//review:
	char buf[] = "OKOK\n";
	char *p = "shut up\n";
	// 把buf的内容写到stdout代表的文件，显示屏幕
	fputs(buf, stdout);
	fputs(p, stdout);
}

int main(int argc, char* argv[])
{
	//review(); 
	
	FILE *fp = NULL;
	fp = fopen("08.txt", "w");
	if(fp == NULL){
		return -1;
	}

	char *p1 = "hello\n";
	fputs(p1, fp);
	char *p2 = "nmabi\n";
	fputs(p2, fp);

	// 指针数组
	char *p[] = {"Lanzhou\n","Yancheng\n","Shanghai\n"};
	int i;
	int n = sizeof(p)/sizeof(p[0]);
	for(i=0; i<n; i++){
		fputs(p[i], fp);
	}

	fclose(fp);

    return 0;
}
