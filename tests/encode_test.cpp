#include <gtest/gtest.h>
#include "../src/ascii85.h"
#include <cstdint>
#include <stdexcept>

TEST(EncodeTest, ZeroBlock) {
    std::string input(4, '\0');
    std::string expected = "z";
    std::string result = ascii85::encode_ascii85(input);
    ASSERT_EQ(result, expected);
}

TEST(EncodeTest, PartialBlock) {
    std::string input = "a";
    std::string expected = "<~!1~>";
    std::string result = ascii85::encode_ascii85(input);
    ASSERT_EQ(result, expected);
}

TEST(EncodeTest, MixedData) {
    std::string input = "test";
    std::string expected = "9jqoC"; 
    std::string result = ascii85::encode_ascii85(input);
    ASSERT_EQ(result, expected);
}
