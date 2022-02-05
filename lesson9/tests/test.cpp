#include "CppUTest/TestHarness.h"

int count_ones_a (uint32_t);
int count_ones_b (uint32_t);
int count_ones_c (uint32_t);

TEST_GROUP(CountOnesA)
{
};
TEST(CountOnesA, verA1)
{
  int x = count_ones_a(0b001);
  CHECK_EQUAL(1, x);
}

TEST(CountOnesA, verA2)
{
  int x = count_ones_a(0b0101);
  CHECK_EQUAL(2, x);
}

TEST_GROUP(CountOnesB)
{
};

TEST(CountOnesB, verB1)
{
  int x = count_ones_b(0b001);
  CHECK_EQUAL(1, x);
}

TEST(CountOnesB, verB2)
{
  int x = count_ones_b(0b0101);
  CHECK_EQUAL(2, x);
}

TEST_GROUP(CountOnesC)
{
};

TEST(CountOnesC, verC1)
{
  int x = count_ones_c(0b001);
  CHECK_EQUAL(1, x);
}

TEST(CountOnesC, verC2)
{
  int x = count_ones_c(0b0101);
  CHECK_EQUAL(2, x);
}

TEST(CountOnesC, verC3)
{
  int x = count_ones_c(0x3003);
  CHECK_EQUAL(4, x);
}