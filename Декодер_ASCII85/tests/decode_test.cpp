#include <gtest/gtest.h>
#include "../src/decoder.cpp"

TEST(DecodeTest, ZeroBlock) {
    std::string input = "z";
    std::vector<uint8_t> expected{0, 0, 0, 0};
    auto result = decode(input);
    EXPECT_EQ(result, expected);
}

TEST(DecodeTest, PartialBlock) {
    std::string input = "!@#";
    std::vector<uint8_t> expected{0x01, 0x02};
    auto result = decode(input);
    EXPECT_EQ(result, expected);
}

TEST(DecodeTest, InvalidLength) {
    std::string input = "abc";
    EXPECT_THROW(decode(input), std::invalid_argument);
}

TEST(DecodeTest, InvalidCharacter) {
    std::string input = "abcde!";
    EXPECT_THROW(decode(input), std::invalid_argument);
}
