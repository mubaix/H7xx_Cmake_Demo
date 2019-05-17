#include<stdio.h>
#define N 10
void inv(int *x,int n)
{
    int t,i;
    for(i=0;i<=(n-1)/2;i++)
    {
        t=*(x+i);
        *(x+i)=*(x+n-1-i);
        *(x+n-1-i)=t;
    }
}
void main()
{
    int i,a[N];
    for(i=0;i<N;i++)
        scanf("%d",a+i);
    printf("yuan xu wei:\n");
    for(i=0;i<N;i++)
        printf("%6d",a[i]);
    inv(a,10);
    printf("\n");
    printf("ni xu wei:\n");
    for(i=0;i<N;i++)
        printf("%6d",*(a+i));
    printf("\n");
}