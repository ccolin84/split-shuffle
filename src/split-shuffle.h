#include <fstream>
#include <vector>

struct SplitShufflerArgs
{
  std::string input_file_name = "in.txt";
  std::string output_file_name = "out.txt";
  std::string temp_file_prefix = "temp-file-";
  std::string temp_file_suffix = ".txt";
  size_t max_items_to_hold_in_memory = 1000;
};

struct SplitShufflerResult
{
  bool failed;
  std::string failure_reason = "";
};

class SplitShuffler
{
private:
  std::string input_file_name;
  std::string output_file_name;
  std::string temp_file_prefix;
  std::string temp_file_suffix;
  size_t max_items_to_hold_in_memory;

  std::vector<int> item_buffer;
  std::vector<std::string> temp_file_names;

  size_t count_input_nums() const;
  size_t get_number_of_temp_files(size_t) const;
  std::string get_temp_file_name(size_t) const;
  void set_temp_file_names(size_t);
  std::vector<std::ofstream> get_temp_file_ofstreams();
  void place_nums_in_random_temp_files();
  void write_shuffled_chunks_to_outfile();
  size_t fill_buffer_from_file(std::string &);
  void write_item_buffer_to_outfile() const;
  void delete_temp_files() const;
  void print_item_buffer() const;

public:
  SplitShuffler(SplitShufflerArgs &);
  SplitShufflerResult shuffle();
};