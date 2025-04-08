CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
GTEST_DIR = /usr/src/gtest  # Путь к Google Test
GTEST_LIB = -lgtest -lgtest_main

all: ascii85 tests

ascii85: src/encoder.cpp src/decoder.cpp main.cpp
    $(CXX) $(CXXFLAGS) -o ascii85 $^

tests: tests/decode_test.cpp tests/encode_test.cpp
    $(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -I../src $^ -o tests $(GTEST_LIB)

clean:
    rm -f ascii85 tests
