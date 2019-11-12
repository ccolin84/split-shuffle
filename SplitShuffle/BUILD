# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "pch",
  srcs = [],
  hdrs = ["pch.h"],
  deps = [],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "SplitShuffle",
  srcs = ["SplitShuffle.cpp"],
  hdrs = ["SplitShuffle.h", "Shuffle.h"],
  deps = [":pch"],
  visibility = ["//cli:__pkg__", "//tests:__pkg__"],
)