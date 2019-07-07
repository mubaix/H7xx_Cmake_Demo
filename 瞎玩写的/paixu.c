#include<stdio.h>
#define N 10
void main()
{
	int b[10],i,j,t,max,max_i;
	for(i=0;i<N;i++)
		scanf("%d",&b[i]);
	for(i=0;i<N-1;i++)
	{
		max=b[i];
		max_i=i;
		for(j=i+1;j<N;j++)
		{
			if(b[j]>max)
			{
				max=b[j];
				max_i=j;
			}
		}
		if(i!=max_i)
		{
			t=b[i];
			b[i]=b[max_i];
			b[max_i]=t;
		}
	}
	for(i=0;i<N;i++)
		printf("%4d",b[i]);
	printf("\n");
}