/*************************************************************************
  @File Name: 形参中的数组.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月28日 星期三 15时19分37秒
 ************************************************************************/

#include <stdio.h>

extern void print_array(int arr[], int n);

int main(int argc, char* argv[])
{
	int a[] = {-1, 2,3,4,7,0};
	int n = sizeof(a)/sizeof(*a);
	print_array(a, n); // 传的是数组首地址


	int j = 0;
	int i = 0;
	int tmp;
	// 冒泡
	for(i = 0; i < n; i++){
		for(j = 0; j < n-1-i; j++){
			if(a[j] > a[j+1]){
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}

	print_array(a, n);

	return 0;
}

// 形参中的数组，不是数组，是指针变量 a[]等价 *a
// 编译器认为形参中  a[],a[100],*a是一样的
// 形参中的数组是指针变量，非形参中的数组是普通数组
void print_array(int a[], int n){
    int i = 0;
    
	for(i = 0; i < n; i++){
		printf("%d\n", a[i]);
    }
}
