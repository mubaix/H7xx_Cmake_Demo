#include "stdio.h"
void main()
{
	char a;
	printf("请输入一个小写字母");
	scanf("%c", &a);
	printf("八进制%o,十进制%d,十六进制%#x,字符%c", a, a, a, a);
}