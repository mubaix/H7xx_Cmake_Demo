#include <stdio.h>
void main()
{
    char a[] = "abcdef";
    char *b = "ABCDEF";
    int i;
    for (i = 0; i < 3; i++)
        printf("%c,%s\n", *a, b + i);
    printf("-------------------------\n");
    for (i = 3; a[i]; i++)
    {
        putchar(*(b + i));
        printf("%c\n", *(a + i));
    }
}