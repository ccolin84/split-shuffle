#include <fstream>

namespace data_creator
{
/*
 * Writes number_of_input_numbers between min_number
 * and max_number to file_name
 */
void populate_file_with_ints(
    const std::string &file_name,
    const size_t number_of_input_numbers = 100,
    const size_t min_number = 0,
    const size_t max_number = 1000)
{
  std::ofstream out_file(file_name);

  for (size_t i = 0; i < number_of_input_numbers; i++)
  {
    const unsigned int random_number = (rand() % (max_number - min_number)) + min_number;
    out_file << random_number << '\n';
  }

  out_file.close();
}

/*
 * Counts lines in a file
 */
size_t count_lines(const std::string &file_name)
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
