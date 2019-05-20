#define NL printf("\n");
#include<stdio.h>
void main()
{
    int i,j,*p,a[4][3]={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    printf("\n%d\t%d\t%d\t%d\n",a[0],a[1],a[2],a[3]);
    for(p=a[0]+2,i=0;i<10;i++)
    {
        printf("%5d",*p++);
    }
    NL
    for(i=0;i<4;i++)
    {
        printf("%d",*(a+i));
        for(j=0,p=*(a+i)+j;j<3;j++)
        {
            printf("%5d",*p++);
        }
        NL
    }
}