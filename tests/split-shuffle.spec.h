#include "SplitShuffle/SplitShuffle.h"

void split_shuffler_spec()
{
    test::TestGroup("SplitShuffler", []() {
        test::TestGroup("SplitShuffler", []() {
            test::TestCase(
                "First Test",
                "No Test Yet",
                []() {
                    return test::TestResult{false};
                })
                .run();
        })
            .run();
    })
        .run();
}
