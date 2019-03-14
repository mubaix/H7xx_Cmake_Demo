#include<stdio.h>
#include<math.h>
int main(void)
{
    int a,b,c;
    printf("请输入一元二次方程的待定系数abc，以英文逗号分隔，按回车确定：");
    scanf("%d,%d,%d",&a,&b,&c);

    double delta;
    double x1;
    double x2;

    delta=b*b-4*a*c;
    if (delta>0)
    {
        x1=(-b+sqrt(delta))/(2*a);
        x2=(-b-sqrt(delta))/(2*a);
        printf("该答案有两解,x1=%f,x2=%f\n",x1,x2);
    }
    else if(delta=0)
    {
        x1=(-b)/(2*a);
        x2=x1;
        printf("该答案只有一解,x2=x1=%f\n",x1);
    }
    else
    {
        printf("无解\n");
    }
    return 0;
}