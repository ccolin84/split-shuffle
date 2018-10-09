#include <iostream>
#include "split-shuffler.h"

constexpr char input_file_name[] = "in.txt";
constexpr char output_file_name[] = "out.txt";

int main(int argc, char **argv)
{
  SplitShufflerArgs args;
  args.max_items_to_hold_in_memory = 10;
  args.input_file_name = input_file_name;
  args.output_file_name = output_file_name;
  SplitShuffler shuffler = SplitShuffler(args);
  SplitShufflerResult result = shuffler.shuffle();
  if (result.failed)
  {
    std::cout << "Shuffler failed!\nReason: "
              << result.failure_reason << std::endl;
  }
  return 0;
}