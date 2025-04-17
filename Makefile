CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
GTEST_LIB = -lgtest -lgtest_main

all: ascii85 tests

ascii85: src/encoder.cpp src/decoder.cpp main.cpp
        $(CXX) $(CXXFLAGS) -o ascii85 $^ $(GTEST_LIB)

tests: tests/decode_test.cpp tests/encode_test.cpp
        $(CXX) $(CXXFLAGS) -Isrc $^ -o tests $(GTEST_LIB)

clean:
        rm -f ascii85 tests
