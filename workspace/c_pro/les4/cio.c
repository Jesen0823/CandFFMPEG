#include <stdio.h>

/*
 * Linux把任何东西当做文件，引入stdio.h后会分配一系列指针
 * stdin 标准输入流默认是键盘
 * stdout标准输出流默认是显示器
 * stderr标准错误流
 *
 * */
int main()
{
    printf("hello cio!\n");
    int a;
    scanf("%d", &a); // input 
    printf("input value is :%d\n",a);

    // 写入数据函数，stdout默认是显示器.以下等价于printf("please input value b:\n")
    fprintf(stdout, "please input value b :\n");
    int b;
    // stdin默认键盘，等价scanf("%d", &b)
    fscanf(stdin, "%d", &b);
    if(b < 0){
        fprintf(stderr, "the value must > 0.");
        return 1;
    }

    return 0;
}
