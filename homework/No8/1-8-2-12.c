#include<stdio.h>
int a[10];
void search(int *t,int n,int *a)
{
    int k,m;
    m=t[0];
    for(k=1;k<n;k++)
        if(m>t[k])
            m=t[k];
    *a=m;
}
void main()
{
    int i,min,*p=a;
    for(i=0;i<10;i++)
        scanf("%d",a+i);
    search(a,10,p);
    printf("min=%d\n",min);
}