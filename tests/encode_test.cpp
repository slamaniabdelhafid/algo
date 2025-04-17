#include <gtest/gtest.h>
#include "../src/ascii85.h" 
#include <cstdint>         
#include <stdexcept>        

TEST(EncodeTest, ZeroBlock) {
    std::vector<uint8_t> data{0, 0, 0, 0};
    std::string expected = "z";
    auto result = encode(data);
    EXPECT_EQ(result, expected);
}

TEST(EncodeTest, PartialBlock) {
    std::vector<uint8_t> data{0x01, 0x02};
    std::string expected = "!@#";
    auto result = encode(data);
    EXPECT_EQ(result, expected);
}

TEST(EncodeTest, MixedData) {
    std::vector<uint8_t> data{0xFF, 0x00, 0x7F, 0x80};
    std::string expected = "~uZV";
    auto result = encode(data);
    EXPECT_EQ(result, expected);
}

TEST(EncodeTest, PartialBlockWithPadding) {
    std::vector<uint8_t> data{0x01, 0x02};
    std::string expected = "<~!@#~>";
    auto result = encode(data);
    EXPECT_EQ(result, expected);
}

TEST(DecodeTest, PartialBlockWithPadding) {
    std::string input = "<~!@#~>";
    std::vector<uint8_t> expected{0x01, 0x02};
    auto result = decode(input);
    EXPECT_EQ(result, expected);
}
