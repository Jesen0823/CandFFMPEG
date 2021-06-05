/*************************************************************************
  @File Name: 字符串查找.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月27日 星期二 13时52分37秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argv, char* argc[]){

	char buf[] = "kafkaopp";
	// 查询字符，如果存在返回字符地址
	char *ret = strchr(buf, 'a');
	char *ret2 = strstr(buf,"kao");
	printf("ret2 = %s\n", ret2);
	if(ret == NULL){
		printf("查询失败\n");
	}else{
		printf("查询结果：%s\n",ret);
	}
	return 0;
}
