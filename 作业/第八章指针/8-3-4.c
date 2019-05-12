#include <stdio.h>
void main()
{
    int a[3][4] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
    int(*p)[4] = a, i, j, k = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 2; j++)
            k += *(*(p + i) + j);
    printf("%d\n", k);
}