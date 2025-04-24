# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Isrc -Itests -pthread

# Google Test flags
GTEST_LIBS = -lgtest -lgtest_main

# Files
SRC = src/encoder.cpp src/decoder.cpp
MAIN = main.cpp
TESTS = tests/encode_test.cpp tests/decode_test.cpp

# Outputs
BIN = ascii85
TEST_BIN = test_ascii85

# Object files
OBJS = $(SRC:.cpp=.o)
MAIN_OBJ = $(MAIN:.cpp=.o)
TEST_OBJS = $(TESTS:.cpp=.o)

all: $(BIN) $(TEST_BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN) $(TEST_BIN)
