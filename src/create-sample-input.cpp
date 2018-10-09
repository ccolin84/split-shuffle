#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "data-creator.h"

/*

  A program to generate a sample input file of integers
  separated by newlines to run the shuffle program on

*/

constexpr size_t min_number = 0, max_number = 1000;
constexpr char sample_input_data_file_name[] = "in.txt";

int main(int argc, char **argv)
{
  // determine the number of input numbers to create (default to 500)
  size_t number_of_input_numbers = 500;
  size_t user_input_number = 0;

  // if the user gives a cli argument, use that if it is a valid int > 0
  if (argc > 1 && (user_input_number = atoi(argv[1])))
  {
    number_of_input_numbers = user_input_number;
  }

  std::cout << "Writing "
            << number_of_input_numbers
            << " random numbers to "
            << sample_input_data_file_name
            << "..."
            << std::endl;

  data_creator::populate_file_with_ints(
      sample_input_data_file_name,
      number_of_input_numbers,
      min_number,
      max_number);

  std::cout
      << "Done!" << std::endl;

  return 0;
}