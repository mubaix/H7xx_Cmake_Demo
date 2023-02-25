#include<stdio.h>
#define NL printf("\n");
void main()
{
    int a[4][3]={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    int (*p1)[3],(*p2)[3];
    p1=a;
    p2=a;
    NL
    printf("1:%d,%d",*(*(p1+0)),*(*(p2+0)));
    NL
    p1++;
    p2++;
    printf("2:%d,%d",*p1[0],*p2[0]);
    NL
    printf("3:%d,%d",*(*(p1+1)+2),*(*(p2+1)+2));
    NL
}