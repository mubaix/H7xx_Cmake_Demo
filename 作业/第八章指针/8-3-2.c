#include <stdio.h>
void main()
{
    int a, b, c;
    int x = 4, y = 6, z = 8;
    int *p1 = &x, *p2 = &y, *p3;
    a = p1 == &x;
    b = 3 * (-*p1) / (*p2) + 7;
    c = *(p3 = &z) = *p1 * (*p2);
    printf("%d,%d,%d\n", a, b, c);
}