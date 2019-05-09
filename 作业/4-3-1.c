#include "stdio.h"
void main()
{
	int a;
	printf("请输入一个数字:");
	scanf("%d", &a);
	if (a % 17 == 0)
		printf("%d可以被17整除", a);
	else
		printf("%d不可以被17整除", a);
}