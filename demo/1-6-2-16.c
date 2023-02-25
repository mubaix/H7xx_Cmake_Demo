#include<stdio.h>
#define N 80
int main()
{
    char s1[2*N],s2[N];
    int i=0,j=0;
    printf("请输入两个字符串，以空格或回车结束：");
    scanf("%s",s1);
    scanf("%s",s2);
    while(s1[i]!='\0')
        i++;
    while(s2[j]!='\0')
        s1[i++]=s2[j++];
    s1[i]='\0';
    printf("连接后的两个字符串为：%s\n",s1);
    return 0;
}