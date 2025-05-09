#include "ascii85.h"
#include <gtest/gtest.h>

TEST(Ascii85Test, Encode) {
    EXPECT_EQ(ascii85::encode("hello"), "<~BOu!rDZ~>");
    EXPECT_EQ(ascii85::encode("Man"), "<~9jqo~>");
    EXPECT_EQ(ascii85::encode(""), "<~~>");
}

TEST(Ascii85Test, EncodeNullBytes) {
    std::string null_bytes(4, '\0'); 
    EXPECT_EQ(ascii85::encode(null_bytes), "<~z~>");
}

TEST(Ascii85Test, Decode) {
    EXPECT_EQ(ascii85::decode("<~BOu!rDZ~>"), "hello");
    EXPECT_EQ(ascii85::decode("9jqo"), "Man");
    EXPECT_EQ(ascii85::decode("<~~>"), "");
    EXPECT_EQ(ascii85::decode("z"), std::string(4, '\0'));
}
