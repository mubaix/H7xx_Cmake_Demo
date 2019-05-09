#include "stdio.h"
void main()
{
	float a, b;
	printf("请输入工时:");
	scanf("%f", &a);
	if (a < 40)
		printf("薪水为:%.2f", b = a * 8);
	else
		printf("薪水为:%.2f", b = 320 + (a - 40) * 12);
}