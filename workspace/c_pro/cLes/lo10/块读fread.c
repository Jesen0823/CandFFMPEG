/*************************************************************************
  @File Name: 块读fread.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 23时32分31秒
 ************************************************************************/


#include <stdio.h>

/* fread()方法：
 * 如果文件大小  > 用户指定的块大小, 返回值为用户指定的块数目
 * 如果文件大小  > 用户指定的块大小, 返回文件大小或0
 * 第二个参数(块大小)设为1，很大可能不会返回0
 * */

typedef struct Student{
	char name[20];
	int score;
}Stu;

int main(int argc, char* argv[])
{
	FILE *fp = fopen("01.txt", "r");
	if(fp == NULL){
		return -1;
	}

	Stu s[10];

	// 逐个读结构体
	int ret;
	int i = 0;
	while(1){
		// ret = fread(s+i, 1, sizeof(Stu), fp) // 等价
		ret = fread(&s[i], 1, sizeof(Stu), fp);
		printf("ret = %d\n", ret);
		if(ret == 0){ // 读取结束
			printf("end of read.\n");
			break;
		}
		i++;
	}

	int num = i;
	for(i=0; i < num; i++){
		printf("%s, %d\n", s[i].name, s[i].score);
	}


	fclose(fp);
	fp = NULL;

    return 0;
}
