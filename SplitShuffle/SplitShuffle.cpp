#include "pch.h"
#include "SplitShuffle.h"
#include "Shuffle.h"

SplitShuffler::SplitShuffler(SplitShufflerArgs &args)
    : input_file_name(args.input_file_name),
      output_file_name(args.output_file_name),
      temp_file_prefix(args.temp_file_prefix),
      temp_file_suffix(args.temp_file_suffix),
      max_items_to_hold_in_memory(args.max_items_to_hold_in_memory),
      item_buffer(args.max_items_to_hold_in_memory)
{
}

SplitShufflerResult SplitShuffler::shuffle()
{
  const size_t number_of_inputs = this->count_input_nums();

  // validate the input file contents
  if (number_of_inputs == 0)
  {
    return {true, "No numbers to sort!"};
  }
  if (number_of_inputs == 1)
  {
    return {true, "One number is already sorted!"};
  }

  const size_t number_of_temp_files = this->get_number_of_temp_files(number_of_inputs);
  this->set_temp_file_names(number_of_temp_files);
  // first pass of mixing the numbers
  this->place_nums_in_random_temp_files();
  // second pass of shuffling the random chunks
  this->write_shuffled_chunks_to_outfile();
  // clean up temp files
  this->delete_temp_files();

  return {false};
}

/*
 * Counts the number of lines in the input file
 */
size_t SplitShuffler::count_input_nums() const
{
  std::ifstream input_file(this->input_file_name);
  std::string line;
  size_t count = 0;

  while (std::getline(input_file, line))
  {
    ++count;
  }

  input_file.close();
  return count;
}

inline size_t SplitShuffler::get_number_of_temp_files(const size_t num_inputs) const
{
  double items_per_file = (double)num_inputs / (double)this->max_items_to_hold_in_memory;
  return (size_t)std::ceil(items_per_file);
}

std::string SplitShuffler::get_temp_file_name(const size_t file_number) const
{
  return this->temp_file_prefix + std::to_string(file_number) + this->temp_file_suffix;
}

void SplitShuffler::set_temp_file_names(const size_t num_temp_files)
{
  if (this->temp_file_names.size())
  {
    this->temp_file_names.clear();
  }

  this->temp_file_names.reserve(num_temp_files);
  for (size_t i = 0; i < num_temp_files; i++)
  {
    const std::string temp_file_name = this->get_temp_file_name(i);
    this->temp_file_names.push_back(temp_file_name);
  }
}

void SplitShuffler::place_nums_in_random_temp_files() const
{
  std::vector<std::ofstream> temp_file_ofstreams = this->get_temp_file_ofstreams();
  std::ifstream input_file(this->input_file_name);

  const size_t num_temp_files = temp_file_ofstreams.size();

  // keep track of how many items we've put in each temp file
  std::vector<int> num_in_temp_file_at_inx(num_temp_files);

  std::string line;
  unsigned int rand_inx;
  while (std::getline(input_file, line))
  {
    rand_inx = rand() % num_temp_files;

    // make sure a single temp file doesn't get too big
    while (num_in_temp_file_at_inx[rand_inx] == this->max_items_to_hold_in_memory)
    {
      rand_inx = rand() % num_temp_files;
    }

    temp_file_ofstreams[rand_inx] << line << '\n';
    num_in_temp_file_at_inx[rand_inx]++;
  }

  // close file streams
  input_file.close();
  std::for_each(std::begin(temp_file_ofstreams), std::end(temp_file_ofstreams), [](std::ofstream &out_stream) {
    out_stream.close();
  });
}

std::vector<std::ofstream> SplitShuffler::get_temp_file_ofstreams() const
{
  std::vector<std::ofstream> temp_file_output_streams;
  temp_file_output_streams.reserve(this->temp_file_names.size());
  for (const std::string temp_file_name : this->temp_file_names)
  {
    temp_file_output_streams.push_back(std::ofstream(temp_file_name));
  }
  return temp_file_output_streams;
}

void SplitShuffler::write_shuffled_chunks_to_outfile()
{
  remove(this->output_file_name.c_str());
  for (const std::string temp_file_name : this->temp_file_names)
  {
    this->fill_buffer_from_file(temp_file_name);
    shuffle::inplace_fisher_yates_shuffle<int>(this->item_buffer);
    this->write_item_buffer_to_outfile();
  }
}

void SplitShuffler::write_item_buffer_to_outfile() const
{
  std::ofstream output_file = std::ofstream(this->output_file_name, std::ofstream::app);
  std::for_each(std::begin(this->item_buffer), std::end(this->item_buffer), [&output_file](const int num) {
    output_file << num << '\n';
  });
  output_file.close();
}

size_t SplitShuffler::fill_buffer_from_file(const std::string &in_file_name)
{
  std::ifstream input_file(in_file_name);
  size_t num_ints_read = 0;
  std::string line;

  // make sure the buffer is clear before using it
  if (this->item_buffer.size())
  {
    this->item_buffer.clear();
  }

  while (num_ints_read < this->max_items_to_hold_in_memory && std::getline(input_file, line))
  {
    this->item_buffer.push_back(atoi(line.c_str()));
    ++num_ints_read;
  }

  input_file.close();
  return num_ints_read;
}

void SplitShuffler::delete_temp_files() const
{
  for (const std::string temp_file_name : this->temp_file_names)
  {
    remove(temp_file_name.c_str());
  }
}