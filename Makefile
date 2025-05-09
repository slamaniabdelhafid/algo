CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
GTEST_LIBS = -lgtest -lgtest_main -pthread

TARGET = ascii85
TEST_TARGET = test_ascii85

SRC = ascii85.cpp main.cpp
TEST_SRC = ascii85.cpp test.cpp

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)
	python3 test_random.py

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
