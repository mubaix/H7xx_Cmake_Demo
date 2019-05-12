#include <stdio.h>
void main()
{
    int a[] = {4, 5, 6};
    int i, *p;
    p = a;
    for (i = 0; i < 3; i++)
        printf("%d,%d,%d,%d\n", a[i], p[i], *(p + i), *(a + i));
}