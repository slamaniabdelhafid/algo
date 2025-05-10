CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS =

# Targets
TARGET = shannon_coder
TEST_TARGETS = test_encoder test_decoder

# Sources
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN_OBJ = main.o

TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGETS)
	./test_encoder
	./test_decoder

test_encoder: $(filter-out $(MAIN_OBJ), $(OBJS)) tests/test_encoder.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_decoder: $(filter-out $(MAIN_OBJ), $(OBJS)) tests/test_decoder.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(TEST_TARGETS) $(OBJS) $(MAIN_OBJ) $(TEST_OBJS)
