#include <vector>
#include <ctime>

namespace shuffle
{
template <typename T>
void inplace_fisher_yates_shuffle(std::vector<T> &numbers_to_shuffle)
{
  srand(time(0));
  for (size_t i = numbers_to_shuffle.size() - 1; i > 0; i--)
  {
    unsigned int rand_inx = rand() % i;
    std::iter_swap(std::begin(numbers_to_shuffle) + i, std::begin(numbers_to_shuffle) + rand_inx);
  }
}
}
