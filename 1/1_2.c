# include<math.h>
# include<stdio.h>
void main()
{
    float x,y;
    printf("input number:\n");
    scanf("%f",&x);
    y=2*sqrt(x)+1;
    printf("2*sqrt(%f)+1=%f\n",x,y);
}