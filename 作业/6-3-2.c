#include "stdio.h"
void main()
{
    int a[30], b[6], i, sum = 0;
    for (i = 0; i < 30; i++)
    {
        a[i] = 2 + 2 * i;
        sum = sum + a[i];
        if (i % 5 == 4)
        {
            b[i / 5] = sum / 5.0;
            sum = 0;
        }
    }
    for (i = 0; i < 6; i++)
        printf("%d\t", b[i]);
}