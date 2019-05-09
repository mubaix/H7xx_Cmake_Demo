#include "stdio.h"
void main()
{
	int a, b, c, max;
	printf("请输入3个整数，用空格键分隔:");
	scanf("%d %d %d", &a, &b, &c);
	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	printf("最大的数为:%d", max);
}