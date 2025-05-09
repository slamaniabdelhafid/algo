CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -Iinclude -Wall -Wextra
LDFLAGS = -lgtest -lgtest_main -pthread
EIGEN_FLAGS = -I/usr/include/eigen3

TARGET = bin/gaussian_solver
TEST_TARGET = bin/gaussian_tests

# Source files
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRCS))

# Test files
TEST_DIR = test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,obj/%.o,$(TEST_SRCS))

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) $^ -o $@

$(TEST_TARGET): $(filter-out obj/main.o,$(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) $^ -o $@ $(LDFLAGS)

obj/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) -c $< -o $@

obj/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

test-samples: $(TARGET)
	@./$(TARGET) samples/input.csv samples/output.csv
	@diff -q samples/output.csv samples/expected_output.csv && echo "Sample test passed!" || (echo "Sample test failed!"; exit 1)

clean:
	rm -rf obj bin samples/output.csv

.PHONY: all test test-samples clean
