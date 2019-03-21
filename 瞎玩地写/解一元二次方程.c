# include<stdio.h>
# include<math.h>
void main()
{
    float a,b,c,disc,x1,x2,p,q;
    printf("请输入一元二次方程的系数（a,b,c）：");
    scanf("%f,%f,%f",&a,&b,&c);
    disc=b*b-4*a*c;
    if(fabs(a)<=1e-6)
    {
        printf("这是一元一次方程！");
        printf("x=%.2f\n",-c/b);
    }
    else
    {
        if(fabs(disc)<=1e-6)
        printf("x1=x2=%.2f\n",-b/(2*a));
        else
        {
            if(disc>0)
            {
                x1=(-b+sqrt(disc))/(2*a);
                x2=(-b-sqrt(disc))/(2*a);
                printf("x1=%.2f,x2=%.2f\n",x1,x2);
            }
            else
            {
                p=-b/(2*a);
                q=sqrt(fabs(disc))/(2*a);
                printf("x1=%.2f+%.2fi\n",p,q);
                printf("x2=%.2f-%.2fi\n",p,q);
            }
            
        }
        
    }
    
}