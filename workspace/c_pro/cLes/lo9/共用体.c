/*************************************************************************
  @File Name: 共用体.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月29日 星期四 23时31分07秒
 ************************************************************************/

#include <stdio.h>

union Test{

	unsigned char a;
	unsigned short b;
	unsigned int c;
};

/*共用体也叫联合体
 * 1.结构体大小涉及字符对齐
 * 2.共用体的大小为最大成员的大小
 * 3.共用体公用一块地址，所有成员地址都一样
 * 4.给某成员赋值会影响到其他成员
 * */
int main(int argc, char* argv[])
{
	printf("size is %d\n", sizeof(union Test));
	union Test obj;
	printf("%ld, %p, %p, %p\n",&obj, &obj.a, &obj.b, &obj.c);
    // 高位放高地址，低位放低地址
	obj.c = 0x443311;
	printf("obj.c = %x\n", obj.c);
	printf("obj.b = %x\n", obj.b);
	printf("obj.a = %x\n", obj.a);

	obj.a = 0xaa;
	printf("then obj.c = %x\n", obj.c);
	printf("then obj.b = %x\n", obj.b);
	printf("then obj.a = %x\n", obj.a);

	return 0;
}
