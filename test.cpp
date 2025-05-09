#include "ascii85.h"
#include <gtest/gtest.h>

TEST(Ascii85Test, Encode) {
    EXPECT_EQ(ascii85::encode("hello"), "<~BOu!rDZ~>");
    EXPECT_EQ(ascii85::encode("Man"), "<~9jqo~>");
    EXPECT_EQ(ascii85::encode(""), "<~~>");
    EXPECT_EQ(ascii85::encode("\0\0\0\0", 4), "<~z~>");
}

TEST(Ascii85Test, Decode) {
    EXPECT_EQ(ascii85::decode("<~BOu!rDZ~>"), "hello");
    EXPECT_EQ(ascii85::decode("9jqo"), "Man");
    EXPECT_EQ(ascii85::decode("<~~>"), "");
    EXPECT_EQ(ascii85::decode("z"), std::string(4, '\0'));
}

TEST(Ascii85Test, RoundTrip) {
    const std::string test = "Test\x00\xFF\n";
    EXPECT_EQ(ascii85::decode(ascii85::encode(test)), test);
}

TEST(Ascii85Test, InvalidInput) {
    EXPECT_THROW(ascii85::decode("Invalid!"), std::runtime_error);
}
