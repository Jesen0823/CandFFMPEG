#include <stdio.h>

int main()
{
    char str[] = "hello";
    char *str2 = "world"; // 字符指针
    char str3[10]; // 字符数组

    printf("input the value:\n");
    scanf("%s\n", str3);
    scanf("%s\n", str);
    printf("str is %s\n", str);
    printf("str2 is %s\n", str2);
    printf("str3 is %s\n", str3);
    
}
