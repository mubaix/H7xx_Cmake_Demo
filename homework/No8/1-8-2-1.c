#include <stdio.h>
void main()
{
    int i, j, *p, *q;
    p = &i;
    q = &j;
    i = 5;
    j = 8;
    printf("%d,%d,%d,%d\n", i, j, p, q);
    printf("%d,%d\n", &i, *&i);
    printf("%d,%d\n", &j, *&j);
}