# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
  name = "SplitShuffleTests",
  srcs = [
    "run-tests.cpp",
    "test.h", 
    "shuffle.spec.h",
    "split-shuffle.spec.h", 
    "split-shuffle.test.h",
    "data-creator.h"
    ],
  copts = [],
  deps = ["//SplitShuffle:SplitShuffle"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
  name = "CreateSampleInput",
  srcs = ["create-sample-input.cpp", "data-creator.h"],
  copts = [],
  deps = [],
)