/*************************************************************************
  @File Name: 二进制读写结构体.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月02日 星期日 13时03分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 二进制读写结构体，
 *1. 如果边读边写，是没有问题的，因为分配的堆空间没有释放掉
 *2. 如果先写，程序运行完再读取，会段错误。因为堆空间已经释放掉了，再读就是野指针
 *3. 解决办法是先读写结构体，再单独读写指针变量
 * */

typedef struct Student{
	// 如果是指针变量，写文件时，只是把指针写进去
	char *name;
	int id;
	int name_len;
}Stu;

/*将结构体以二进制存放到文件，并读取
 *
 * */

void write_file(Stu *s){
	FILE *fp = fopen("04.txt", "w");

	// 先写结构体
	int ret = fwrite(s, sizeof(Stu), 1, fp);
	if(ret < 0){
		perror("write struct error.\n");
		return;
	}

	// 再写结构体包含的指针变量
	ret = fwrite(s->name, s->name_len, 1, fp);
	if(ret < 0){
		perror("fwrite s.name error.\n");
		return;
	}

	fclose(fp);
	fp = NULL;
}


void read_file(){
	FILE *fp = NULL;
	fp = fopen("04.txt", "r");

	// 先读结构体
	Stu s;
	int ret = fread(&s, sizeof(Stu), 1, fp);
	printf("read ret = %d\n", ret);
	if(ret < 0){
		perror("read error\n");
		return;
	}
	
	// 再读字符串
	s.name = malloc(s.name_len + 1);
	//	解决乱码
	memset(s.name, 0, s.name_len + 1);

	ret = fread(s.name, s.name_len, 1, fp);
	if(ret < 0){
		perror("read s.name error\n");
		return;
	}
	printf("read result:\n %s %d %d\n", s.name, s.id, s.name_len);
	free(s.name);

	fclose(fp);
	fp = NULL;
}

int main(int argc, char* argv[])
{
/*	
	Stu s;

	s.id =1;
	s.name_len = strlen("Jesen");
	s.name = (char *)malloc(s.name_len + 1);
	strcpy(s.name, "Jesen");

	write_file(&s);
	free(s.name);
*/
	read_file();
    return 0;
}
