#include "lib/split-shuffler.h"
#include "test-lib/test.h"

void split_shuffler_spec()
{
  test::TestGroup("SplitShuffler", []() {
    test::TestGroup("SplitShuffler", []() {
        test::TestCase(
            "Failing Test",
            "Failing Test2",
            []() {
                return test::TestResult{true, "Failed!"};
            }).run();
        }).run();
    }).run();
}
