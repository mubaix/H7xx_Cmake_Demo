#include<stdio.h>
int max(int x,int y)
{
    int z;
    if(x>y)
        z=x;
    else
        z=y;
    return(z);
}
void main()
{
    int a,b,c;
    int max(int x,int y);
    scanf("%d,%d",&a,&b);       /*运行输入第一个数后输入逗号，在输入第二个数*/
    c=max(a,b);
    printf("max=%d\n",c);
    
}