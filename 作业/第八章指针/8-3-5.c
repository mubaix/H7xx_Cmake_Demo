#include <stdio.h>
void main()
{
    int k = 0, sign, m;
    char s[] = "-12345";
    if (s[k] == '+' || s[k] == '-')
        sign = s[k++] == '+' ? 1 : -1;
    for (m = 0; s[k] > '0' && s[k] <= '9'; k++)
        m = m * 10 + s[k] - '0';
    printf("result=%d\n", sign * m);
}