#include<stdio.h>
#include<math.h>
int f(int n)
{
    int x,y,z;
    for(x=1,y=0;x<n;x++)
    {
        if(n%x==0)
            y++;
        if(y>1)
            break;
    }
    if(y==1)
        z=1;
    else
        z=0;
    return z;
}
void main()
{
    int n;
    printf("please input a number:");
    scanf("%d",&n);
    printf("%d\n",f(n));
}