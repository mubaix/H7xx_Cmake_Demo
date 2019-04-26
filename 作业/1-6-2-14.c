#include<stdio.h>
#include<string.h>
#define N 81
void main()
{
    char ch[N];
    int i,count=0;
    puts("please input chars:");
    gets(ch);
    for(i=0;i<strlen(ch);i++)
        if(ch[N]!='\n')
            count++;
    printf("count=%d\n",count);
}