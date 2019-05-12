#include<stdio.h>
#define N 11
void main()
{
    int i,j,a[N][N];
    for( i = 1; i < N; i++)
    {
        a[i][i]=1;
        a[i][1]=1;
    }
    for( i = 3; i < N; i++)
    {
        for(j=2;j<=i-1;j++)
            a[i][j]=a[i-1][j-1]+a[i-1][j];
    }
    for(i=1;i<N;i++)
    {
        for(j=1;j<=i;j++)
            printf("%6d",a[i][j]);
        printf("\n");
    }
    
}