#include<stdio.h>
#define PI 3.1415926
void main()
{
    float r,s;
    printf("请输入圆的半径r=");
    scanf("%f",&r);
    s=PI*r*r;
    printf("s=%f\n",s);
}