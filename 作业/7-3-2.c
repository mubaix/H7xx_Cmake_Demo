#include <stdio.h>
void f(int a[][4], int n, int hang[], int lie[])
{
    int i, j,n;
    for (i = 0; i < n; i++)
        hang = 0;
    for (j = 0; j < 4; j++)
        lie = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < 4; j++)
        {
            hang[i] += a[i][j];
            lie[j] += a[i][j];
        }
    printf("%d\n", hang[i]);
    printf("%d\n", lie[j]);
}