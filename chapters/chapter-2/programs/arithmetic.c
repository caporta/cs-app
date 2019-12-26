#include <stdio.h>

int main()
{
  printf("Overflow: %d\n", 200 * 300 * 400 * 500);

  printf("Non-Associative: %f <=> %f\n", (3.14+1e20)-1e20, 3.14+(1e20-1e20));
}
