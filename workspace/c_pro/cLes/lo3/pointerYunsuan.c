#include <stdio.h>

int main(){

    int a = 3;
    int b = 2;
    int array[3];
    int *pa = array;//array本身是地址，赋值给指针可以不需要加&符号
    array[0] = 1; // 等价pa[0] = 1;
    array[1] = 10;
    array[2] = 100;
    int *p = &a;
    int i;
    for(i = 0; i < 6; i++){
        printf("1, *p=%d\n", *p);
        p++; // 指针移动
    }
    printf("--------------------------------------\n");
    p = &a;

    for(i = 0; i < 6; i++){
        printf("2, p[%d]=%d\n",i, p[i]);
    }

}
