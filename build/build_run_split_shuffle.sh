g++ -o bin/run-split-shuffle.o src/run-split-shuffle.cpp -c -std=c++17 && \
g++ \
  bin/run-split-shuffle.o \
  bin/split-shuffle.o \
  -o bin/run-split-shuffle \
  -std=c++17