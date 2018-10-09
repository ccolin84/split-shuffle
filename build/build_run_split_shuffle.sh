g++ -Wall -o bin/run-split-shuffle.o src/run-split-shuffle.cpp -c -std=c++17 && \
g++ -Wall \
  bin/run-split-shuffle.o \
  bin/split-shuffler.o \
  -o bin/run-split-shuffle \
  -std=c++17