#include "ascii85.h"
#include <vector>
#include <cstdint>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace {

const uint32_t POW85[] = {85*85*85*85, 85*85*85, 85*85, 85, 1};

void encode_chunk(const uint8_t* chunk, size_t len, std::string& out) {
    if (len == 4 && *(uint32_t*)chunk == 0) {
        out += 'z';
        return;
    }

    uint32_t value = (chunk[0] << 24) | 
                     (chunk[1] << 16) | 
                     (chunk[2] << 8) | 
                     chunk[3];

    char buf[5];
    for (int i = 0; i < 5; ++i) {
        buf[i] = static_cast<char>((value / POW85[i]) % 85 + 33);
    }
    out.append(buf, len + 1);
}

} // namespace

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

std::string decode(const std::string& data) {
    std::string clean;
    bool in_z_block = false;
    
    // Strip delimiters
    size_t start = (data.size() >= 2 && data.substr(0, 2) == "<~") ? 2 : 0;
    size_t end = (data.size() >= 2 && data.substr(data.size() - 2) == "~>") 
               ? data.size() - 2 : data.size();
    
    // Process characters
    for (size_t i = start; i < end; ++i) {
        char c = data[i];
        if (std::isspace(c)) continue;
        
        if (c == 'z') {
            if (!clean.empty()) throw std::runtime_error("'z' inside group");
            in_z_block = true;
            continue;
        }

        if (c < '!' || c > 'u') {
            throw std::runtime_error("Invalid ASCII85 character");
        }
        clean += c;
    }

    std::string result;
    if (in_z_block) {
        result.append(4, '\0');
    }

    // Decode 5-byte groups
    for (size_t i = 0; i < clean.size(); i += 5) {
        uint32_t value = 0;
        size_t group_len = std::min(static_cast<size_t>(5), clean.size() - i);
        
        for (size_t j = 0; j < group_len; ++j) {
            value += (clean[i + j] - 33) * POW85[j];
        }

        // Output exactly 4 bytes
        for (size_t j = 0; j < 4; ++j) {
            if (j < (4 - (5 - group_len))) {
                result += static_cast<char>((value >> (24 - 8 * j)) & 0xFF);
            }
        }
    }
    
    return result;
}

} // namespace ascii85
