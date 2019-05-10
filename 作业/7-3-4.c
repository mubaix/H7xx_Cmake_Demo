#include<stdio.h>
int f(char ch[])
{
    int i=0,j=0;
    while(ch[i]!='#')
    {
        if(ch[i++]==' ')
        {
            if(ch[j]>='a'&&ch[j]<='z')
                ch[j]-=32;
            j=i;
        }
    }
    return ch[j];
}