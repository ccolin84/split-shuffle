g++ -Wall \
  tests/run_tests.cpp \
  -o bin/tests \
  src/split-shuffler.cpp \
  -I src/ \
  -std=c++17