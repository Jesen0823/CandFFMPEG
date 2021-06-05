/*************************************************************************
  @File Name: 随机位置光标.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年05月02日 星期日 11时54分15秒
 ************************************************************************/

/* fseek(fp, 0, SEEK_SET);从开头偏移0个位置，回到开头
 * fseek(fp, x, SEEK_SET);右偏移x个字节，-x左移
 * fseek(fp, x, SEEK_END);
 * fseek(fp, x, SEEK_CUR);从当前位置偏移x字节
 * 开头处不允许左移，末尾处可以右移
 *
 * */
#include <stdio.h>

typedef struct Student{
	char name[20];
	int score;
}Stu;

int main(int argc, char* argv[])
{
	FILE *fp = fopen("02.txt", "r");

	Stu s;
	// 读取第4个结构体
	// 右偏移3个结构体
	fseek(fp, 3*sizeof(Stu), SEEK_SET);
	fread(&s, 1, sizeof(Stu), fp);
	printf("to right 3 step and read:\n %s %d\n", s.name, s.score);

	// 回到最开始位置
	fseek(fp, 0, SEEK_SET);
	fread(&s, 1, sizeof(Stu), fp);
	printf("back start and read:\n %s %d\n", s.name, s.score);

	// 获取文件大小，移动光标到末尾
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	printf("file size = %ld\n", size);

	fclose(fp);

	return 0;
}
