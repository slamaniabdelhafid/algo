#include "ascii85.h"
#include <vector>
#include <cstdint>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace ascii85 {

std::string encode(const std::string& data) {
    std::string output = "<~";
    size_t i = 0;
    const size_t len = data.size();

    while (i < len) {
        uint32_t chunk = 0;
        int bytes = 0;

        // Pack 4 bytes into a 32-bit chunk
        while (bytes < 4 && i < len) {
            chunk = (chunk << 8) | static_cast<uint8_t>(data[i++]);
            bytes++;
        }

        // Special case for 4 null bytes
        if (bytes == 4 && chunk == 0) {
            output += 'z';
            continue;
        }

        // Convert to ASCII85
        char encoded[5];
        for (int j = 4; j >= 0; --j) {
            encoded[j] = static_cast<char>(chunk % 85 + 33);
            chunk /= 85;
        }
        
        // Append only the needed characters
        output.append(encoded, bytes + 1);
    }

    return output + "~>";
}

std::string decode(const std::string& input) {
    std::string clean;
    
    // Strip delimiters
    if (input.size() >= 2 && input.substr(0, 2) == "<~") {
        clean = input.substr(2);
    } else {
        clean = input;
    }

    if (clean.size() >= 2 && clean.substr(clean.size() - 2) == "~>") {
        clean = clean.substr(0, clean.size() - 2);
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
        for (size_t i = 0; i < group.size() + 1; ++i) {
            if (i < 4) {
                result += static_cast<char>((value >> (24 - 8 * i)) & 0xFF);
            }
        }
    }

    return result;
}

} // namespace ascii85
