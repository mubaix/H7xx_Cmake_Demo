#include "stdio.h"
void main() 
{
  int a, b, a1, b1;
  scanf("%d,%d", &a, &b);
  a1 = a;
  b1 = b;
  a = b1;
  b = a1;
  printf("a=%d,b=%d", a, b);
}