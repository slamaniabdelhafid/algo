#include "ascii85.h"
#include <vector>
#include <cstdint>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace ascii85 {

std::string encode(const std::string& data) {
    std::string result = "<~";
    const size_t len = data.size();
    
    for (size_t i = 0; i < len; i += 4) {
        uint8_t chunk[4] = {0};
        size_t chunk_len = std::min(static_cast<size_t>(4), len - i);
        
        for (size_t j = 0; j < chunk_len; ++j) {
            chunk[j] = static_cast<uint8_t>(data[i + j]);
        }
        encode_chunk(chunk, chunk_len, result);
    }
    
    return result + "~>";
}


std::string decode(const std::string& input) {
    std::string clean;
    
    // Strip delimiters
    if (input.size() >= 2 && input.substr(0, 2) == "<~") {
        clean = input.substr(2, input.size() - 4); // Remove both <~ and ~>
    } else {
        clean = input;
    }

    std::string result;
    std::vector<uint8_t> group;

    for (char c : clean) {
        if (std::isspace(c)) continue;

        if (c == 'z') {
            if (!group.empty()) {
                throw std::runtime_error("'z' inside group");
            }
            result.append(4, '\0');
            continue;
        }

        if (c < '!' || c > 'u') {
            throw std::runtime_error("Invalid ASCII85 character");
        }

        group.push_back(c - 33);
        if (group.size() == 5) {
            uint32_t value = 0;
            for (int i = 0; i < 5; ++i) {
                value = value * 85 + group[i];
            }

            // Output exactly 4 bytes
            for (int i = 0; i < 4; ++i) {
                result += static_cast<char>((value >> (24 - 8 * i)) & 0xFF);
            }
            group.clear();
        }
    }

    // Handle partial group (1-4 remaining chars)
    if (!group.empty()) {
        uint32_t value = 0;
        size_t padding = 5 - group.size();
        
        // Pad with 'u' (ASCII 117, code 84)
        for (size_t i = 0; i < group.size(); ++i) {
            value = value * 85 + group[i];
        }
        for (size_t i = 0; i < padding; ++i) {
            value = value * 85 + 84;
        }

        // Output only the real bytes (not padding)
        for (size_t i = 0; i < 4 - padding; ++i) {
            result += static_cast<char>((value >> (24 - 8 * i)) & 0xFF);
        }
    }

    return result;
}

} // namespace ascii85
