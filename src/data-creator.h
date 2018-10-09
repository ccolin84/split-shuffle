#include <fstream>

namespace data_creator
{
// function for writing a number to the sample input file
void populate_file_with_ints(
    std::string file_name,
    size_t number_of_input_numbers = 100,
    size_t min_number = 0,
    size_t max_number = 1000)
{
  std::ofstream out_file(file_name);

  for (size_t i = 0; i < number_of_input_numbers; i++)
  {
    unsigned int random_number = (rand() % (max_number - min_number)) + min_number;
    out_file << random_number << '\n';
  }

  out_file.close();
}

// function for counting the number of entries in a file
size_t count_entries_in_file(std::string file_name)
{
  std::ifstream input_file(file_name);
  std::string line;
  size_t count = 0;

  while (std::getline(input_file, line))
  {
    ++count;
  }

  input_file.close();
  return count;
}
} // namespace data_creator