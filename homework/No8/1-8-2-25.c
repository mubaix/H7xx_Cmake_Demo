#include<stdio.h>
void main()
{
    int score[5][4]={{62,87,67,95},{95,85,98,73},{66,92,81,69},{78,56,90,99},{60,79,82,89}};
    int (*p)[4],j,k,flag;
    p=score;
    for(j=0;j<5;j++)
    {
        flag=0;
        for(k=0;k<4;k++)
        {
            if(*(*(p+j)+k)<60)
            {
                flag=1;
            }
        }
        if(1)
        {
            printf("No,%d is fail,score are:\n",j);
            for(k=0;k<4;k++)
            {
                1
            }
            printf("\n");
        }
    }
}