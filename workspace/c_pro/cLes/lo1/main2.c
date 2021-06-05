#include <stdio.h>
#define R 10
// 宏函数,优点是不需要指定参数类型
// 宏的另一个功能是根据不同设置条件编译不同程序部分，产生不同的目标代码文件
#define N(n) n*10
#define ADD(a,b) a+b
#define ADD2(a,b) (a+b)

int add(int a, int b){
    return a+b;
}

// 作用：给一个变量类型取别名
// 宏不管写在哪里全局都可以使用，而typedef是有作用域的
typedef int iin;
typedef int *p;
p q = NULL; // int *q = NULL

// size_t 实际上就是unsigned long size_t的别名
// eg. typedef unsigned long size_t

// 结构体起别名stu_t
typedef struct stu{
    
}stu_t;



int main(int argv, char* argc[])
{
    iin a1 = 9;
    printf("typedef iin a=%d \n",a1);

    //struct stu_t stu1;// 结构体使用

    int a = R;
    printf("hell main!\n");
    printf("a=%d \n",a);

    int b = N(a);
    printf("b = Na is :%d\n",b);

    int c = add(a,b);
    printf("add a,b is:%d\n",c);

    int d = ADD(a,b);
    printf("ADD a,b is:%d\n",d);

    // 宏是单纯字符串替换 int e = a+b*a+b;
    int e = ADD(a,b) * ADD(a,b);
    printf("ADD * ADD is %d ,result is ERROR!\n",e);
    int f = ADD2(a,b) * ADD2(a,b);
    printf("ADD2 * ADD2 is:%d, result is true.\n",f);


    return 0;
}
