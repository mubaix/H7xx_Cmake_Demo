# include"stdio.h"
void main()
{
    float sum=0,a;
    int n=1;
    do
    {
        a=1.0/(n*(n+1));
        sum=sum+a;
        n=n+1;
    }
    while (a>0.001);
    printf("sum=%f",sum);
}