#include "split-shuffle.h"

constexpr char input_file_name[] = "in.txt";
constexpr char output_file_name[] = "out.txt";

int main(int argc, char **argv)
{
  SplitShufflerArgs args;
  args.max_items_to_hold_in_memory = 10;
  SplitShuffler shuffler = SplitShuffler(args);
  shuffler.shuffle();
  return 0;
}