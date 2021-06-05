/*************************************************************************
  @File Name: 块读写fwrite.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月01日 星期六 22时33分03秒
 ************************************************************************/

#include <stdio.h>

/* fwrite()
 * 1,需要写的变量的首地址
 * 2，写入内容的块大小
 * 3， 写入文件的块的数目
 * 4，fp,文件句柄
 * 返回值：成功时为写入的块的数目
 * ******************************
 * fread()
 * 1,放置读取文件内容的变量地址
 * 2，读取文件内容的块大小
 * 3，读取文件的块数目
 * 返回值：成功，返回读取的块数目
 * */

typedef struct Student{
	char name[20];
	int score;
}Stu;

int main(int argc, char* argv[])
{
	FILE *fp = fopen("01.txt", "w");

	// 写文件
	Stu stu1 = {"Coke", 78};
	int ret = fwrite(&stu1, sizeof(Stu), 1, fp);
	printf("ret = %d\n", ret);
	/*
	int ret2 = fwrite(&stu1, 1, sizeof(Stu), fp);
	printf("ret2 = %d\n", ret2);
	*/

	Stu stu[4] = {
		"Jesen", 98,
		"Zhang", 78,
		"Zhu", 82,
		"Zhou", 75
	};
	int rets = fwrite(stu, sizeof(stu), 1, fp);
	printf("rets = %d\n", rets);

	fclose(fp);
	fp = NULL;

	// 读取二进制文件
	fp = fopen("01.txt", "r");
	Stu ss[5];
	int ret_r = fread(&ss[0], sizeof(Stu), 4, fp);
	printf("read result ret_r:%d\n", ret_r);
	int i = 0;
	for(i=0; i< 4; i++){
		printf("%s %d\n", ss[i].name, ss[i].score);
	}

	fclose(fp);
	fp = NULL;
	return 0;
}
