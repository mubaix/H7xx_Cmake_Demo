#include<stdio.h>
#define N 10
void main()
{
    int i,j,min,temp,a[N]={1,5,4,3,7,0,9,8,2,6};
    for(i=0;i<N-1;i++)
    {
        min=i;
        for(j=i+1;j<N;j++)
            if(a[min]>a[j])
                min=j;
        if(min!=i)
        {
            
        }
    }
}