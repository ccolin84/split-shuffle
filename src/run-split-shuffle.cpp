#include <iostream>
#include <filesystem>
#include "lib/split-shuffler.h"

char default_input_file_name[] = "in.txt";
char output_file_name[] = "out.txt";

int main(int argc, char **argv)
{
  char* input_file_name = default_input_file_name;

  // use an input file name if one is passed
  if (argc > 1) {
    input_file_name = argv[1];
  }

  if (!std::filesystem::exists(input_file_name)) {
    std::cout << input_file_name << " doesn't exist!";
    exit(1);
  }

  std::cout << "Sorting file " << input_file_name;

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
