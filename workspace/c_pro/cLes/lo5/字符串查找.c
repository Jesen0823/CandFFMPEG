/*************************************************************************
  @File Name: 字符串查找.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 21时21分47秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char *s = "ifyouknowyousaydonotknow";
	int i = 0;
	char *tmp = NULL;

	while(1){
		// 查找匹配字符串
		tmp = strstr(s, "ou");
		if(tmp ==NULL){
			break;
		}else{
			i++;
			// 重新设置寻找起点
			s = tmp + strlen("ou");
		}
	}
	printf("重新次数:%d\n", i);

	  return 0;
}
