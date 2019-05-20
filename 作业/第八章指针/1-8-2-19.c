#include<stdio.h>
#include<string.h>
void main()
{
    char s[7];
    int n;
    int chnum(char *p);
    1
    if(s[0]=='-')
        n=-chnum(s+1);
    else if(*s=='+')
        n=chnum(s+1);
    else
        n=chnum(s);
    printf("%d\n",n);
}
int chnum(char *p)
{
    int num=0,k,len,j;
    len=strlen(p);
    for(;*p!='\0';p++)
    {
        k=
        j=(--len);
        while(j>0)
        {
            k=k*10;
            j--;
        }
        1
    }
    return(num);
}