#include <stdio.h>
void main()
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    int *p, i, s = 1;
    p = a;
    for (i = 0; i < 6; i++)
        s *= *(p + i);
    printf("%d\n", s);
}