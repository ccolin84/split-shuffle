#include "SplitShuffle/Shuffle.h"

void shuffle_spec()
{
    test::TestGroup("shuffle", []() {
        test::TestCase(
            "inplace_fisher_yates_shuffle",
            "should shuffle an input vector",
            []() {
                int input_vector_size = 20;
                auto input = std::vector<int>();
                input.reserve(input_vector_size);
                for (int i = 0; i < input_vector_size; i++)
                {
                    input.push_back(i);
                }
                auto shuffled_input = std::vector(input);

                shuffle::inplace_fisher_yates_shuffle(shuffled_input);

                if (input == shuffled_input)
                {
                    return test::TestResult{true, "Failed!"};
                }
                return test::TestResult{false};
            })
            .run();
    })
        .run();
}
