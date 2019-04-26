#include<stdio.h>
void main()
{
    int i,j,row,col,min;
    int a[3][4]={{1,2,3,4},{9,8,7,6},{-1,-2,0,5}};
    min=a[0][0];
    row=col=0;
    for(i=0;i<3;i++)
        for(j=0;j<4;j++)
            if(min>a[i][j])
            {
                min=a[i][j];
                row=i;
                col=j;
            }
    printf("min=%d,row=%d,col=%d\n",min,row,col);
}