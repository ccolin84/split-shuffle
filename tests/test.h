#pragma once

#include <functional>
#include <iostream>

/*
 * Simple utilities for building and running test suites
 * within the project.
 *
 * TestResult - returned from a test case to indicate the result
 * TestCase - a single function that returns a TestResult
 * TestGroup - provides a way to group TestCases
 */

namespace test
{

/*
 * Provides a logical grouping for running test cases
 * These can be nested for more granular grouping
 */
class TestGroup
{
private:
  std::string group_name;
  std::function<void()> test_functions;

  std::string get_bar()
  {
    return std::string(50, '-');
  }

public:
  TestGroup(std::string group_name, std::function<void()> test_functions)
      : group_name(group_name),
        test_functions(test_functions)
  {
  }

  void run()
  {
    std::cout << this->get_bar()
              << '\n'
              << "Testing "
              << this->group_name
              << '\n'
              << this->get_bar()
              << '\n'
              << std::endl;

    this->test_functions();

    std::cout << this->get_bar()
              << std::endl;
  }
};

/*
 * Result of running a test case
 * allows the attaching of a reason if it fails
 */
struct TestResult
{
  bool failed;
  std::string failure_reason;
};

/*
 * Wraps a single test case and
 * prints out the result when run
 */
class TestCase
{
private:
  std::string test_name;
  std::string test_description;
  std::function<TestResult()> test_function;

  void print_error_message(std::string &&msg)
  {
    std::cout << "\033[1;31m"
              << msg
              << "\033[0m\n"
              << std::endl;
  }

  void print_success_message(std::string &&msg)
  {
    std::cout << "\033[1;32m"
              << msg
              << "\033[0m\n"
              << std::endl;
  }

public:
  TestCase(std::string test_name, std::string test_description, std::function<TestResult()> test_function)
      : test_name(test_name),
        test_description(test_description),
        test_function(test_function){};

  void run()
  {
    TestResult test_result = this->test_function();
    if (test_result.failed)
    {
      this->print_error_message("FAILED: " + this->test_name);
      this->print_error_message(std::forward<std::string>(this->test_description));
      this->print_error_message(std::forward<std::string>(test_result.failure_reason));
    }
    else
    {
      this->print_success_message("PASSED: " + this->test_name);
    }
  }
};
} // namespace test
