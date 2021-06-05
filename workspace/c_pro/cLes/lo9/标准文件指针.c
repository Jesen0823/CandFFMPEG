/*************************************************************************
  @File Name: 标准文件指针.c
  @Author: jesen
  @Mail:xie_stacol@163.com
  @Created Time: 2021年04月30日 星期五 17时38分23秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("aaaaaaaaa\n");
	fclose(stdout);// 关闭标准输出文件指针，即关闭了文件输出与屏幕的关联
	// 下一句将无法输出
	printf("bbbbbbb\n");

	// 打印库函数调用失败的原因
	perror("jesen");
	fclose(stderr); // 关闭标准错误指针，perror将无法继续打印错误
	perror("jesen0823");
    
	int a;
	printf("输入数字a:");
	fclose(stdin); // 调用关闭标准输入，将无法输入a的值
	scanf("%d",&a);
	printf("a= %d\n", a); // 无法打印，因为调用了fclose(stdout);

	

	return 0;
}
