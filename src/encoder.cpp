#include "ascii85.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdint>

namespace ascii85 {

std::string encode_ascii85(const std::string& input) {
    std::string output = "<~";
    size_t i = 0;

    while (i < input.size()) {
        uint32_t chunk = 0;
        int len = 0;

        for (int j = 0; j < 4; ++j) {
            chunk <<= 8;
            if (i < input.size()) {
                chunk |= static_cast<unsigned char>(input[i++]);
                ++len;
            }
        }

        if (chunk == 0 && len == 4) {
            output += 'z';
        } else {
            char encoded[5];
            for (int j = 4; j >= 0; --j) {
                encoded[j] = static_cast<char>(chunk % 85 + 33);
                chunk /= 85;
            }
            output.append(encoded, encoded + len + 1);
        }
    }

    output += "~>";
    return output;
}

} 
