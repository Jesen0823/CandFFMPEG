/*************************************************************************
  @File Name: shuzu.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月26日 星期一 21时43分59秒
 ************************************************************************/

#include <stdio.h>

int main(int argv, char* argc[]){

  int a1[4] = {1,2,3,4}; // 正确的数组初始化
  int a2[4] = {0};  // 正确，部分初始化剩下的自动为0
  int a3[4];
  //a3 = {1,2,3,4} //error,数组不是变量
  
  int n = sizeof(a1)/sizeof(a1[0]);
  int max = a1[0];
  int i = 0;
  for(i;i < n; i++){
	max = a1[i];
  }
  printf("max is :%d\n",max);


  return 0;
}
