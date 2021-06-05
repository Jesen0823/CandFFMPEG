#include <stdio.h>

/*
 *函数的递归
 调用函数本身
 函数调用通过栈保存调用者的地址

 * */

void func(){
 printf("func ...\n");
 func();
}

// 求一个数的阶乘
int funcc(int n){
    int r;
    if(n < 0){
        printf("Error! input must > 0.\n");
    }else if(n == 0 | n == 1){
        r = 1;
    }else{
        r = n* funcc(n-1);
    }

    return r;
}

int main()
{
    int n;
    printf("please input n:\n");
    scanf("%d",&n);

    int result = funcc(n);
    printf("result is %d \n",result);


    return 0;
}
