#include <iostream>
#include <fstream>
#include <stdlib.h>

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
  unsigned int user_input_number = 0;

  // if the user gives a cli argument, use that if it is a valid int > 0
  if (argc > 1 && (user_input_number = atoi(argv[1])))
  {
    number_of_input_numbers = user_input_number;
  }

  std::ofstream sample_input_data_file(sample_input_data_file_name, std::ofstream::out);

  // function for writing a number to the sample input file
  auto write_number_to_sample_input_file = [&sample_input_data_file](const int num) {
    sample_input_data_file << num << '\n';
  };

  for (size_t i = 0; i < number_of_input_numbers; i++)
  {
    unsigned int random_number = rand() % max_number;
    write_number_to_sample_input_file(random_number);
  }

  sample_input_data_file.close();

  return 0;
}