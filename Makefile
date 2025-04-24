# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc -I/usr/include -pthread
GTEST_LIBS = -lgtest -lgtest_main

# Файлы
SRC = src/encoder.cpp src/decoder.cpp
MAIN = main.cpp
TEST_FILES = tests/encode_test.cpp tests/decode_test.cpp

# Цели
BIN = ascii85
TEST_BIN = test_ascii85

# Объектные файлы
OBJS = $(SRC:.cpp=.o)
MAIN_OBJ = $(MAIN:.cpp=.o)
TEST_OBJS = $(TEST_FILES:.cpp=.o)

all: $(BIN) $(TEST_BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN): $(OBJS) $(TEST_OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f *.o $(BIN) $(TEST_BIN)
