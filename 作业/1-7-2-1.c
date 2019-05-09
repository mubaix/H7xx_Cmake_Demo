#include <stdio.h>
void main()
{
    int a, b, c, m;
    int max(int x, int y);
    printf("input a,b,c:");
    scanf("%d,%d,%d", &a, &b, &c);
    m = max(a, max(b, c));
    printf("max=%d\n", m);
}
int max(int x, int y)
{
    int z;
    z = (x > y) ? x : y;
    return z;
}