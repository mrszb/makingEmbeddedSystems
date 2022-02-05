#include "CppUTest/TestHarness.h"

int count_ones_a (u_int32_t);

TEST_GROUP(CountOnes)
{
};
TEST(CountOnes, verA)
{
  int x = count_ones_a(0b001);
  CHECK_EQUAL(1, x);
}