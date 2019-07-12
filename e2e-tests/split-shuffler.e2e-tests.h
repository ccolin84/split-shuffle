#include "lib/split-shuffler.h"
#include "test-lib/test.h"
#include "src/data-creator.h"

constexpr char test_input_file_name[] = "test-inputs.txt";
constexpr char test_output_file_name[] = "test-outputs.txt";

void split_shuffler_e2e_tests()
{
  test::TestGroup("SplitShuffler", []() {
    test::TestCase(
        "Correct output size given buffer size ==  input size",
        "Outputs the same number of items as the input given the buffer size equals the input size",
        []() {
          size_t num_test_entries = 1000;
          remove(test_input_file_name);
          data_creator::populate_file_with_ints(test_input_file_name, num_test_entries);
          SplitShufflerArgs args;
          args.max_items_to_hold_in_memory = num_test_entries;
          args.input_file_name = test_input_file_name;
          args.output_file_name = test_output_file_name;
          SplitShuffler shuffler(args);

          shuffler.shuffle();

          size_t output_file_entries = data_creator::count_lines(test_output_file_name);
          remove(test_input_file_name);
          remove(test_output_file_name);
          if (output_file_entries == num_test_entries)
          {
            return test::TestResult{false};
          }
          else
          {
            std::string error_message =
                "Expected " + std::to_string(output_file_entries) +
                " to equal " + std::to_string(num_test_entries);
            return test::TestResult{true, error_message};
          }
        })
        .run();

    test::TestCase(
        "Correct output size given buffer size > input size",
        "Outputs the same number of items as the input given the buffer size is greater than the input size",
        []() {
          size_t num_test_entries = 1000;
          size_t buffer_size = 2000;
          remove(test_input_file_name);
          data_creator::populate_file_with_ints(test_input_file_name, num_test_entries);
          SplitShufflerArgs args;
          args.max_items_to_hold_in_memory = buffer_size;
          args.input_file_name = test_input_file_name;
          args.output_file_name = test_output_file_name;
          SplitShuffler shuffler(args);

          shuffler.shuffle();

          size_t output_file_entries = data_creator::count_lines(test_output_file_name);
          remove(test_input_file_name);
          remove(test_output_file_name);
          if (output_file_entries == num_test_entries)
          {
            return test::TestResult{false};
          }
          else
          {
            std::string error_message =
                "Expected " + std::to_string(output_file_entries) +
                " to equal " + std::to_string(num_test_entries);
            return test::TestResult{true, error_message};
          }
        })
        .run();

    test::TestCase(
        "Correct output size given buffer size < input size",
        "Outputs the same number of items as the input given the buffer size is less than the input size",
        []() {
          size_t num_test_entries = 10000;
          size_t buffer_size = 1000;
          remove(test_input_file_name);
          data_creator::populate_file_with_ints(test_input_file_name, num_test_entries);
          SplitShufflerArgs args;
          args.max_items_to_hold_in_memory = buffer_size;
          args.input_file_name = test_input_file_name;
          args.output_file_name = test_output_file_name;
          SplitShuffler shuffler(args);

          shuffler.shuffle();

          size_t output_file_entries = data_creator::count_lines(test_output_file_name);
          remove(test_input_file_name);
          remove(test_output_file_name);
          if (output_file_entries == num_test_entries)
          {
            return test::TestResult{false};
          }
          else
          {
            std::string error_message =
                "Expected " + std::to_string(output_file_entries) +
                " to equal " + std::to_string(num_test_entries);
            return test::TestResult{true, error_message};
          }
        })
        .run();
  })
      .run();
}
