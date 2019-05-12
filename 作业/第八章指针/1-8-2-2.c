#include <stdio.h>
void main()
{
    int i = 3, j = 8, k = 11, *x, *y, *z, *m;
    x = &i;
    y = &j;
    z = &k;
    m = x;
    if (*x < *y)
        m = y;
    if (*m < *z)
        m = z;
    printf("%d\n", *m);
}