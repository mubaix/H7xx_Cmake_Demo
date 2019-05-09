#include "stdio.h"
void main()
{
    int letter = 0, number = 0, other = 0;
    char ch;
    printf("please input chars:");
    scanf("%c", &ch);
    while (ch != '\n')
    {
        if (ch >= 'A' && ch <= 'Z', ch >= 'a' && ch <= 'z')
            letter++;
        else if (ch >= '0' && ch <= '9')
            number++;
        else
            other++;
        scanf("%c", &ch);
    }
    printf("letter=%d,number=%d,other=%d", letter, number, other);
}