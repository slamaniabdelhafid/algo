CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc
GTEST_LIB = -lgtest -lgtest_main

all: ascii85 test_suite

ascii85: src/encoder.cpp src/decoder.cpp main.cpp
	$(CXX) $(CXXFLAGS) -o ascii85 $^ $(GTEST_LIB)

test_suite: tests/decode_test.cpp tests/encode_test.cpp src/encoder.cpp src/decoder.cpp
	$(CXX) $(CXXFLAGS) -o test_suite $^ $(GTEST_LIB)

clean:
	rm -f ascii85 test_suite
