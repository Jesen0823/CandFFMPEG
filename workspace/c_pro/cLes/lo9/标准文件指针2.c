/*************************************************************************
  @File Name: 标准文件指针2.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 17时57分20秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{

	// printf内部实现是往标准输出设备1写内容
	printf("before aaaaaaa\n");
	// 关掉标准输出指针与屏幕的关联
	//fclose(stdout);
	close(1); // 1就是标准输出设备与上面一样，关闭使之空闲

	// 返回的1会指向最小可以设备，也就是1
	// 标准输出设备1已经与文件txt关联了，所以接下来都会写入文件
	int fd = open("./01_txt", O_WRONLY, 0777);
	printf("验证fd的值, fd=%d\n", fd);

	// 打开与文件的关联
	stdout = fopen("./01.txt", "w");
	if(stdout == NULL){
		printf("open 01.txt fail\n");
		return -1;
	}
	printf("after aaaaaaa\n");

    return 0;
}
