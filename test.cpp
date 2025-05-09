#include "ascii85.h"
#include <gtest/gtest.h>
#include <string>

TEST(Ascii85Test, EncodeBasic) {
    EXPECT_EQ(ascii85::encode("hello"), "<~BOu!rDZ~>");
    EXPECT_EQ(ascii85::encode("Man"), "<~9jqo~>");
    EXPECT_EQ(ascii85::encode(""), "<~~>");
}

TEST(Ascii85Test, EncodeSpecialCases) {
    // Test null bytes encoding to 'z'
    std::string null_bytes(4, '\0');
    EXPECT_EQ(ascii85::encode(null_bytes), "<~z~>");
    
    // Test various string lengths
    EXPECT_EQ(ascii85::encode("A"), "<~!)~>");
    EXPECT_EQ(ascii85::encode("AB"), "<~!)6~>");
    EXPECT_EQ(ascii85::encode("ABC"), "<~!)6a~>");
}

TEST(Ascii85Test, DecodeBasic) {
    EXPECT_EQ(ascii85::decode("<~BOu!rDZ~>"), "hello");
    EXPECT_EQ(ascii85::decode("9jqo"), "Man");
    EXPECT_EQ(ascii85::decode("<~~>"), "");
}

TEST(Ascii85Test, DecodeSpecialCases) {
    // Test 'z' shortcut for null bytes
    EXPECT_EQ(ascii85::decode("z"), std::string(4, '\0'));
    
    // Test various encoded lengths
    EXPECT_EQ(ascii85::decode("!)"), "A");
    EXPECT_EQ(ascii85::decode("!)6"), "AB");
    EXPECT_EQ(ascii85::decode("!)6a"), "ABC");
    
    // Test with whitespace
    EXPECT_EQ(ascii85::decode("<~BO u!r DZ~>"), "hello");
}

TEST(Ascii85Test, RoundTrip) {
    std::string test_strings[] = {
        "Hello World!",
        "ASCII85 encoding",
        "Test with null bytes",
        "Special chars: !@#$%^&*()",
        "Longer string that spans multiple chunks for encoding"
    };
    
    for (const auto& str : test_strings) {
        std::string encoded = ascii85::encode(str);
        std::string decoded = ascii85::decode(encoded);
        EXPECT_EQ(decoded, str);
    }
}

TEST(Ascii85Test, InvalidInput) {
    // Characters outside valid range (33-117)
    EXPECT_THROW(ascii85::decode(" "), std::runtime_error);  // space (32)
    EXPECT_THROW(ascii85::decode("v"), std::runtime_error);  // v (118)
    
    // 'z' in middle of group
    EXPECT_THROW(ascii85::decode("ABzCD"), std::runtime_error);
    
    // Invalid delimiters
    EXPECT_THROW(ascii85::decode("<invalid>"), std::runtime_error);
}
