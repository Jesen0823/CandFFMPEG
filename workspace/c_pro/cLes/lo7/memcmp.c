/*************************************************************************
  @File Name: memcpy.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 14时27分05秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int a1[] = {1,2,3,4,5,6};
	int a2[] = {1,2,3,4,5,7};

	int flag = memcmp(a1, a2, 6*sizeof(int));
	int flag2 = memcmp(a1, a2, 4*sizeof(int));
	printf("flag2 = %d\n", flag2);
	if(flag < 0){
		printf(" a1 < a2\n");
	}else if(flag > 0){
		printf("a1 > a2\n");
	}else{
		printf("a1 = a2\n");
	}



	return 0;
}
