#include "test.h"
#include "split-shuffle.spec.h"
#include "shuffle.spec.h"
#include "split-shuffle.test.h"

int main(int argc, char **argv)
{
  split_shuffler_spec();
  shuffle_spec();
  split_shuffler_e2e_tests();
  return 0;
}
