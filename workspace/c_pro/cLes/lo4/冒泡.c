/*************************************************************************
  @File Name: 冒泡.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月26日 星期一 22时45分34秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
	
	int a[] = {1,9,2,98,5,11,7,-1};
	int len = sizeof(a) / sizeof(a[0]);
	
	int i;
	int j;
	int temp;
	for(i = 0; i < len-1; i++){
		for(j = 0; j < len -1-i;j++){
			if(a[j] > a[j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	for(i = 0; i < len; i++){
		printf("%d\n",a[i]);
	}


	return 0;
}
