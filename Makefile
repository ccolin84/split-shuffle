CXX=g++-9
CXXFLAGS=-Wall -std=c++17 -lstdc++fs -I ./

.PHONY: all clean run-sample test

all: clean bin/tests bin/run-split-shuffle

test: bin/tests
	./bin/tests

run-sample: bin bin/run-split-shuffle sample-input.txt 
	./bin/run-split-shuffle sample_in.txt

bin/run-split-shuffle: bin bin/split-shuffler.o bin/run-split-shuffle.o
	$(CXX) $(CXXFLAGS) \
		bin/run-split-shuffle.o \
		bin/split-shuffler.o \
		-o bin/run-split-shuffle

bin/tests: bin bin/split-shuffler.o
	$(CXX) $(CXXFLAGS) \
		tests/*.cpp \
		bin/split-shuffler.o \
		-o bin/tests

# a sample input file to be sorted
sample-input.txt: bin bin/create-sample-input
	./bin/create-sample-input

# creates a sample input file to be sorted
bin/create-sample-input: bin
	$(CXX) $(CXXFLAGS) \
		src/create-sample-input.cpp \
		-o bin/create-sample-input

bin/run-split-shuffle.o: bin
	$(CXX) $(CXXFLAGS) \
		src/run-split-shuffle.cpp \
		-o bin/run-split-shuffle.o -c

bin/split-shuffler.o: bin
	$(CXX) $(CXXFLAGS) \
		lib/split-shuffler.cpp \
		-o bin/split-shuffler.o -c

bin:
	mkdir bin

clean:
	rm -rf bin/*
