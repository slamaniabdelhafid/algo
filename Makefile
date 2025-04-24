# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -I.        # -I. includes current dir (for ascii85.hpp)

# Google Test flags
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Files
SRC = ascii85.cpp
MAIN = main.cpp
TEST = test.cpp

# Outputs
BIN = ascii85
TEST_BIN = test_ascii85

# Object files
OBJS = $(SRC:.cpp=.o)
MAIN_OBJ = $(MAIN:.cpp=.o)
TEST_OBJ = $(TEST:.cpp=.o)

all: $(BIN) $(TEST_BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN): $(OBJS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#python-tests:
	@echo "Running Python tests..."
	@python3 test_random.py

clean:
	rm -f *.o $(BIN) $(TEST_BIN)
