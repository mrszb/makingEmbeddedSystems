#include <stdlib.h>
#include <stdio.h>
#include "code.h"
int main(void)
{
  int onesA = count_ones_a(0b011);
  printf("onesA=%d\n", onesA);

  int onesB = count_ones_b(0b011);
  printf("onesB=%d\n", onesB);

  int onesC = count_ones_c(0x3003);
  printf("onesC=%d\n", onesC);

  exit(0);
}