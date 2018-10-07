#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

constexpr char input_file_name[] = "in.txt";
constexpr char output_file_name[] = "out.txt";
constexpr size_t pretend_max_ints_fitting_in_ram = 100;

template <typename T>
void inplace_fish_yates_shuffle(std::vector<T> &);

size_t fill_with_n_ints_from_file(size_t, std::vector<int> &, std::ifstream &);

void write_sorted_nums_to_outfile(const std::vector<int> &, std::ofstream &);

int main(int argc, char **argv)
{
  // open input and output files
  std::ifstream input_file(input_file_name);
  std::ofstream output_file(output_file_name);

  std::vector<int> input_chunk;
  input_chunk.reserve(pretend_max_ints_fitting_in_ram);

  std::cout << "Starting shuffle..." << std::endl;
  size_t num_ints_sorted;

  while ((num_ints_sorted = fill_with_n_ints_from_file(pretend_max_ints_fitting_in_ram, input_chunk, input_file)))
  {
    std::cout << "shuffling " << num_ints_sorted << " numbers" << std::endl;
    inplace_fish_yates_shuffle<int>(input_chunk);
    write_sorted_nums_to_outfile(input_chunk, output_file);
    input_chunk.clear();
  }

  std::cout << "Done shuffling" << std::endl;
  // close input and output files
  input_file.close();
  output_file.close();
  return 0;
}

template <typename T>
void inplace_fish_yates_shuffle(std::vector<T> &numbers_to_shuffle)
{
  for (size_t i = numbers_to_shuffle.size() - 1; i > 0; i--)
  {
    unsigned int rand_inx = rand() % i;
    std::iter_swap(std::begin(numbers_to_shuffle) + i, std::begin(numbers_to_shuffle) + rand_inx);
  }
}

size_t fill_with_n_ints_from_file(size_t num_ints_to_read, std::vector<int> &num_container, std::ifstream &input_file)
{
  size_t num_ints_read = 0;
  std::string line;
  while (num_ints_read < num_ints_to_read && std::getline(input_file, line))
  {
    num_container.push_back(atoi(line.c_str()));
    ++num_ints_read;
  }
  return num_ints_read;
}

void write_sorted_nums_to_outfile(const std::vector<int> &sorted_nums, std::ofstream &output_file)
{
  std::for_each(std::begin(sorted_nums), std::end(sorted_nums), [&output_file](int num) {
    output_file << num << '\n';
  });
}
