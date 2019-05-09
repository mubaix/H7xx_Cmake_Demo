#include <stdio.h>
void fun(int a[][4], int n, int row[], int col[])
{
    int i, j;
    for (i = 0; i < n; i++)
        row = 0;
    for (j = 0; j < 4; j++)
        col = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < 4; j++)
        {
            row[i] += a[i][j];
            col[j] += a[i][j];
        }
    printf("%d\n", row[i]);
    printf("%d\n", col[j]);
}