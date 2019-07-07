CXX=g++-9
CXXFLAGS=-Wall -std=c++17 -lstdc++fs -I ./

.PHONY: all clean run-sample

all: clean tests run-split-shuffle

run-sample: sample-input.txt run-split-shuffle
	./bin/run-split-shuffle sample_in.txt

run-split-shuffle: split-shuffler.o run-split-shuffle.o
	$(CXX) $(CXXFLAGS) \
		bin/run-split-shuffle.o \
		bin/split-shuffler.o \
		-o bin/run-split-shuffle

tests: split-shuffler.o
	$(CXX) $(CXXFLAGS) \
		tests/*.cpp \
		bin/split-shuffler.o \
		-o bin/tests

# a sample input file to be sorted
sample-input.txt: create-sample-input
	./bin/create-sample-input

# creates a sample input file to be sorted
create-sample-input:
	$(CXX) $(CXXFLAGS) \
		src/create-sample-input.cpp \
		-o bin/create-sample-input

run-split-shuffle.o:
	$(CXX) $(CXXFLAGS) \
		src/run-split-shuffle.cpp \
		-o bin/run-split-shuffle.o -c

split-shuffler.o: bin
	$(CXX) $(CXXFLAGS) \
		lib/split-shuffler.cpp \
		-o bin/split-shuffler.o -c

bin:
	mkdir bin

clean:
	rm -rf bin/*
