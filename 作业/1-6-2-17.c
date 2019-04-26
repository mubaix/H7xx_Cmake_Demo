#include<stdio.h>
#define N 100
void main()
{
    char ch[N];
    int i;
    printf("please input strings:");
    gets(ch);
    for(i=0;ch[i]!='\0';i++)
    ;
    printf("lenth=%d",i);
}