#include <stdio.h>

/*
 * 结构体的知识
 * */
struct weapon{
    char name[20];
    int atk;
    int price;
}; //结构体类型

struct weapon2{
     char name[20];
     int atk;
     int price;
}weapon2_1; // 声明加定义



int main(int argv, char* argc[])
{
    struct weapon weapon_1 = {
        "gan",
        100,
        200
    }; // 先声明再定义,初始化

    printf("weapon_1 name :%s \n",weapon_1.name);

    // 结构体数组
    //struct weapon weapons[2] = {"kopo",100,90, "yuk",20,25}; 这样也是OK的
    struct weapon weapons[2] = {{"kopo",100,90}, {"yuk",20,25}};
    printf("weapons [0].name is %s, [1].atk is %d \n", weapons[0].name, weapons[1].atk);

    struct weapon *w; // 结构体变量的指针
    w = &weapon_1;
    printf("w .name is %s, w .atk is %d \n",(*w).name, (*w).atk);
    printf("w .name is %s, w .atk is %d \n",w->name, w->atk); // 同上面语句
    
    struct weapon *p;
    p = &weapons; // 指向的是结构体数组第一个元素的起始地址,so p->name 等价 weapons[0].name
    _Bool isSame = (p == &weapons[0]);
    printf("is same first element address:%d\n", isSame);

    printf("p->name is:%s \n",p->name);
    p++; //等价于weapons + 1,即p指向weapons[1]
    printf("p++, then p->name is:%s \n",p->name);

    /*结构体数据类型大小：
     * 涉及字节对齐问题，对齐目的是让计算机能快速读写，以空间换取时间的方式
     * 大小 = 最后一个成员偏移量 + 最后一个成员大小 + 末尾填充字节数
     * 偏移量：某成员实际地址和结构体首地址间的距离，eg.第一个成员偏移是0，第二个成员偏移量是第一个成员的大小，
     * 字节对齐：每个成员相对结构体首地址的偏移量必须等于当前成员的整数倍，如果不是，编译器会在成员之间加上填充字节
     * eg,第一个偏移量是0，大小20，不是第二个成员的4整数倍，所以填充至20，1倍，第三个大小是4填充至20，偏移量是24,
     * 加自身大小4，等于28
     * 最后，判断结构体大小是否是成员中最宽的基本类型成员的整数倍，如果不是，还要在末尾填充至整数倍
     *
     * */
    printf("struct weapon size is :%lu \n", sizeof(struct weapon));
    return 0;    
}
