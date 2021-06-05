#include <stdio.h>
#include <malloc.h>

/*
 *关于动态链表
 * */

struct weapon{
    int price;
    int atk;
    struct weapon * next;
};

struct weapon * create(){
    struct weapon  * head;    // 头节点
    struct weapon  * p1, *p2; // p1指向链表新创建的节点，p2指向上一个节点
    int n = 0;                // 记录当前链表中的节点个数
    
    // 第一个节点,p1p2都指向同一地址
    p1 = p2 =(struct weapon*)malloc(sizeof(struct weapon));
    printf("weapon struct size is %lu \n", sizeof(struct weapon));
    scanf("%d,%d", &p1->price, &p1->atk);
    head = NULL;
    while(p1->price != 0){
        n++;
        printf("n = %d \n",n);
        if(n ==1){
            head = p1; // 第一个元素
        }else{
            p2->next = p1;
        }
        p2 = p1;

        // 开辟新的动态存储区
        p1 = (struct weapon*)malloc(sizeof(struct weapon));
        scanf("%d,%d", &p1->price, &p1->atk);
    }
    p2->next = NULL;
    return (head);
}

int main()
{
    struct weapon *p;
    p = create(); // 链表头指针
    printf("链表第一个节点：%d,%d \n",p->price, p->atk);

    
    return 0;
}
