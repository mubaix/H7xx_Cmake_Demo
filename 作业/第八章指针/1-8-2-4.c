#include <stdio.h>
void main()
{
    int a[] = {1, 3, 5, 7, 9, 11, 13};
    int *p = a;
    printf("1--%d\n", *p);
    printf("2--%d\n", *(++p));
    printf("3--%d\n", *++p);
    printf("4--%d\n", *(p--));
    printf("5--%d\n", *p--);
    printf("6--%d\n", *p++);
    printf("7--%d\n", ++(*p));
    printf("8--%d\n", (*p)++);
    p =& a[2];
    printf("9--%d\n", *p);
    printf("10--%d\n", *(++p));
    p++;
    printf("11--%d\n", *p);
}