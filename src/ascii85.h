#pragma once
#include <string>

namespace ascii85 {
    std::string encode_ascii85(const std::string& input);
    std::string decode_ascii85_to_string(const std::string& input);
}
