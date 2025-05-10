CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = 

# Targets
TARGET = shannon_coder
TEST_TARGET = test_shannon

# Sources
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN_OBJ = main.o

TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lnlohmann_json

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(filter-out $(MAIN_OBJ), $(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lnlohmann_json

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(MAIN_OBJ) $(TEST_OBJS)
