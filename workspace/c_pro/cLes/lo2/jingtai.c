#include <stdio.h>

/*
 *关于动态数据结构
 * */

/*1.静态链表:
 * 头指针head:指向第一个元素的地址
 * 每一个节点，包含了本节点数据和下一节点的地址
 * 链表之间元素的地址不一定是连续的
 *
 * */

// 结构体作为链表的元素
struct weapon{
    int price;
    int atk;
    struct weapon * next;
};

int main()
{
    struct weapon a,b,c, *head; // 3个变量和头指针
    a.price = 100;
    a.atk = 100;
    b.price = 200;
    b.atk = 200;
    c.price = 300;
    c.atk = 300;
    
    // 链接成链表
    head = &a;
    a.next = &b;
    b.next = &c;
    c.next = NULL;

    struct weapon *p;
    p = head;
    while(p!=NULL){
        printf("%d, %d \n",p->atk, p->price);
        p = p->next; // 指针p指向下一个节点
    }
    printf("END.\n");

    return 0;
}
