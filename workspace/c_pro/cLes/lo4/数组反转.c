/*************************************************************************
  @File Name: 数组反转.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月26日 星期一 22时09分49秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){
  
	int a[6] = {0,1,2,3,4,5};
	int len = sizeof(a) / sizeof(a[0]);
	int i = 0;
	int tmp;
	for(i; i < len/2; i++){
		tmp = a[i];
		a[i] = a[len - i -1];
		a[len - i -1] = tmp;
	}

	for(i = 0; i < len; i++){
		printf("%d\n", a[i]);
	}

	int b[] = {1,2,3,4,5,6,7,8,9};
	int n = sizeof(b) / sizeof(b[0]);
	int index = 0; // 首元素下标
	int j = n - 1; // 尾元素下标
	int temp;
	while(index < j){
		temp = b[index];
		b[index] = b[j];
		b[j] = temp;
		index++;
		j--;
	}
	for(i = 0; i < n; i++){
		printf("index[%d] = %d\n", i, b[i]);
	}
	return 0;
}
