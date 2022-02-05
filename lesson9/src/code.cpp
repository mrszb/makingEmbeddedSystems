#include <stdint.h>
#include <iostream>
#include "code.h"

int count_ones_a (uint32_t a)
{
  // slow - goes through all bits
  int count = 0;
  uint32_t mask = 1;

  for (auto ix=0; ix < sizeof(a) * 8; ix++)
  {

    if (a & mask)
      count++;

    mask <<= 1;
  }
    
  return count;
}

int count_ones_b(uint32_t a) {
  int count = 0;

  while(a) {
    if (a & 0b1)
      count++;
      a >>= 1;
  }
  return count;
}

struct Table
{
    constexpr Table() : values()
    {
        values[0] = 0;
        for (auto i = 0; i < 256; ++i)
        {
            values[i] = (i&1) + values[i/2];
        }
    }
    int values[256];
};

int count_ones_c(uint32_t a) {
  constexpr auto table = Table();
  //for (int x =0; x < 256 ; x++)
  //    std::cout << "f(" << x << ") = " << table.values[x] << '\n';

  int count = 0;

  uint8_t * p = (uint8_t *) &a;
  count = table.values[p[0]] + 
  table.values[p[1]] + 
  table.values[p[2]] +	
  table.values[p[3]];
  return count;
}