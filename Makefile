CXX=g++-9
CXXFLAGS=-Wall -std=c++17 -lstdc++fs -I ./

.PHONY: all clean run-sample test

all: clean test bin/run-split-shuffle

test: bin/e2e-tests bin/unit-tests
	./bin/unit-tests
	./bin/e2e-tests

#######################################
#  An Executable To Run On Your File #
#######################################
bin/run-split-shuffle: bin bin/split-shuffler.o bin/run-split-shuffle.o
	$(CXX) $(CXXFLAGS) \
		bin/run-split-shuffle.o \
		bin/split-shuffler.o \
		-o bin/run-split-shuffle
#######################################

#######################################
################ TESTS ################
#######################################
bin/e2e-tests: bin bin/split-shuffler.o
	$(CXX) $(CXXFLAGS) \
		e2e-tests/run-tests.cpp \
		bin/split-shuffler.o \
		-o bin/e2e-tests

bin/unit-tests: bin bin/split-shuffler.o
	$(CXX) $(CXXFLAGS) \
		unit-tests/run-tests.cpp \
		bin/split-shuffler.o \
		-o bin/unit-tests
#######################################

#######################################
# Run Split Shuffle On A Sample Input #
#######################################
run-sample: bin bin/run-split-shuffle sample-input.txt 
	./bin/run-split-shuffle sample_in.txt

# a sample input file to be sorted
sample-input.txt: bin bin/create-sample-input
	./bin/create-sample-input

# creates a sample input file to be sorted
bin/create-sample-input: bin
	$(CXX) $(CXXFLAGS) \
		src/create-sample-input.cpp \
		-o bin/create-sample-input
#######################################

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
