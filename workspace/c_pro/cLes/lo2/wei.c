#include <stdio.h>

/*
 *关于位运算

 按位与   &
 按位或   |
 按位异或 ^
 按位取反 ~
 左移     <<
 右移     >>
 * */

int main()
{
    int a = 4; // 4字节32位 00000000 00000000 00000000 00000100
    int b = 7; //           00000000 00000000 00000000 00000111


               //           00000000 00000000 00000000 00000100 双1为1，对应4
    /*按位与应用：
     * 1.迅速清零：y&0=0
     * 2.保留指定位置：取a的低8位，则把b的低8位都设置为1，即 a&255
     * 3.判断奇数偶数：a&1=1是奇数， a&1=0是偶数
     * */
    int c = a&b;
    printf("& = %d \n",c);


               //           00000000 00000000 00000000 00000111 有1为1，对应7
    /*按位或应用：
     * 1.设定一个数据的指定位：a的低8位设置为1，即 a|255 或a|0xFF
     * */
    int d = a|b;
    printf("| = %d \n",d);

               //           00000000 00000000 00000000 00000011 相异为1，对应3
    /*按位异或应用：
     * 1.定位反转：低8位反转 a^0xFF,即a^255
     * 2.数值交换：a = a^b; b=b^a; a=a^b;
     * */
    int e = a^b;
    printf("^ = %d \n",e);

               //           00000000 00000000 00000000 00000011 按位取反，对应3
    /*按位取反应用：
     * 1.定位反转：低8位反转 a^0xFF,即a^255
     * 2.数值交换：a = a^b; b=b^a; a=a^b;
     * */
    int f = ~a;
    printf("~ = %d \n",f);


               //           00000000 00000000 00000000 01000000 左移，高位丢弃，低位补0
               //           a左移4就是64
    /*左移应用：
     * 1.m左移n位，就等于把m*(2的n次方)
    
     * */
    int g = a<<4;
    printf("<< = %d \n",g);


               //           00000000 00000000 00000000 00000011 相异为1，对应3
               //           右移，如果是有符号，根据符号位左边补0或者补1：
               //           若符号位为0，左边补0，若符号位为1，左边补（根据系统处理方式不同）
    /*右移应用：
     * 1.m右移n位，m/(2的n次方)
     * */
    int h = a>>4;
    printf(">> = %d \n",h);

    return 0;
}
