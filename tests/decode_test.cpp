#include <gtest/gtest.h>
#include "../src/ascii85.h"
#include <cstdint>
#include <stdexcept>

TEST(DecodeTest, ZeroBlock) {
    std::string input = "z";
    std::string expected(4, '\0');
    std::string result = ascii85::decode_ascii85_to_string(input);
    ASSERT_EQ(result, expected);
}

TEST(DecodeTest, PartialBlock) {
    std::string input = "<~!1~>";
    std::string expected = "a";
    std::string result = ascii85::decode_ascii85_to_string(input);
    ASSERT_EQ(result, expected);
}

TEST(DecodeTest, InvalidInput) {
    std::string input = "abcde"; // Недопустимые символы
    EXPECT_THROW(ascii85::decode_ascii85_to_string(input), std::runtime_error);
}
