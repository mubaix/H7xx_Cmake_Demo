#include<stdio.h>
void main()
{
    int a[ ]={2,4,6,8},*p=a,i;
    for(i=0;i<4;i++)
        a[i]=*p++;
    printf("%d,%d\n",a[2],*(--p));
}