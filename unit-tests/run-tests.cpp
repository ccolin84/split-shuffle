#include "test-lib/test.h"
#include "unit-tests/split-shuffler.spec.h"
#include "unit-tests/shuffle.spec.h"

int main(int argc, char **argv)
{
  split_shuffler_spec();
  shuffle_spec();
  return 0;
}
