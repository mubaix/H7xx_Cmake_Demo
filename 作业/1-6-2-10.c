#include <stdio.h>
void main()
{
    int i, j, a[3][3] = {1, 3, 6, 2, 4, 8, 3, 9, 4};
    int s1 = 0, s2 = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (i == j)
                s1 = s1 + a[i][j];
    for (i = 0; i < 3; i++)
        for (j = 2; j >= 0; j--)
            if ((i + j) == 2)
                s2 = s2 + a[i][j];
    printf("s1=%d,s2=%d\n", s1, s2);
}