/*************************************************************************
  @File Name: 两头堵.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 21时31分57秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char *s = "    findtrim   ";
	char *start = s;
	char *end = s + strlen(s) -1;

	// 方向：——>
	while(*start == ' ' && *start != '\0'){
		start++;
	}

	// 方向 <———
	while(*end == ' ' && end != s){
		end --;
	}

	int n = end - start + 1;
	printf("空格数 %d\n", n);

	char buf[100] = "AAAAAAAAAAAAA";
	strncpy(buf, start,n);
	printf("buf = %s\n", buf); // findtrimAAAAA
	buf[n] = 0; // 结束符号
	printf("buf should = %s\n", buf);
	  return 0;
}
