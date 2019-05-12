#include <stdio.h>
void main()
{
    char *ps, s[100];
    int n = 0, i;
    ps = s;
    printf("input a string:");
    gets(ps);
    for (i = 0; *(ps + i) != '\0'; i++)
    {
        if (*(ps + i) == 'm')
            n++;
    }
    if (n > 0)
        printf("there is 'm' in the string,n= %d.\n", n);
    else
        printf("there is no 'm' in the string.\n");
}