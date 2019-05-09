#include <stdio.h>
void main()
{
    int p(int x, int n);
    int x = 5, n = 3;
    printf("p=%d\n", p(x, n));
}
int p(int x, int n)
{
    int i, f = 1;
    for (i = 1; i <= n; i++)
        f = f * x;
    return f;
}