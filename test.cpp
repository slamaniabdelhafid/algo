#include "ascii85.h"
#include <gtest/gtest.h>
#include <string>





TEST(Ascii85Test, EncodeBasic) {
    EXPECT_EQ(ascii85::encode("hello"), "<~BOu!r!!~>");
    EXPECT_EQ(ascii85::encode("Man"), "<~!)6m~>");
    EXPECT_EQ(ascii85::encode(""), "<~~>");
}

TEST(Ascii85Test, EncodeSpecialCases) {
    // Test null bytes encoding to 'z'
    std::string null_bytes(4, '\0');
    EXPECT_EQ(ascii85::encode(null_bytes), "<~z~>");
    
    // Test various string lengths
    EXPECT_EQ(ascii85::encode("A"), "<~!!~>");
    EXPECT_EQ(ascii85::encode("AB"), "<~!!#~>");
    EXPECT_EQ(ascii85::encode("ABC"), "<~!'rq~>");
}


TEST(Ascii85Test, DecodeBasic) {
    EXPECT_EQ(ascii85::decode("<~BOu!rDZ~>"), "hello");
    EXPECT_EQ(ascii85::decode("9jqo"), "Man");
    EXPECT_EQ(ascii85::decode("<~~>"), "");
}



TEST(Ascii85Test, InvalidInput) {
    // Characters outside valid range (33-117)
    EXPECT_NO_THROW(ascii85::decode(" "));  // space (32) is allowed
    EXPECT_THROW(ascii85::decode("v"), std::runtime_error);  // v (118)
    
    // 'z' in middle of group
    EXPECT_THROW(ascii85::decode("ABzCD"), std::runtime_error);
    
    // Invalid characters
    EXPECT_THROW(ascii85::decode("<invalid>"), std::runtime_error);
}

