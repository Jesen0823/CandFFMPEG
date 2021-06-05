# include <stdio.h>

/*
 * 关于共用体
 * */

// 作用：让几个不同的变量共享同一个内存地址
// 优点：节省内存开销
// 缺点：同一时刻只能存储一个成员
union data{
    int a;
    char b;
    int c;
}; // 他们存放到同一个内存单元中，共用体长度是所有成员中最长的长度

int main()
{
    union data data_1;
    data_1.b = 'C';
    data_1.a = 8; // 会覆盖前面的赋值
    printf("union 地址：%d, %d, %d \n",data_1.a,data_1.b,data_1.c);
    return 0;
}
