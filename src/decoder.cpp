#include "ascii85.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> decode(const std::string& encoded) {
    std::vector<uint8_t> result;
    size_t i = 0;


    std::string encoded_str = encoded;

    if (encoded_str.find("<~") == 0) {
        i = 2;
    }
    if (encoded_str.size() >= 2 && encoded_str.substr(encoded_str.size() - 2) == "~>") {
        encoded_str = encoded_str.substr(0, encoded_str.size() - 2);
    }

    while (i < encoded_str.size()) {
        if (encoded_str[i] == 'z') {
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            ++i;
            continue;
        }

        if (encoded_str.size() - i < 5) {
            throw std::invalid_argument("Invalid input length");
        }

        std::vector<uint8_t> digits(5);
        for (size_t j = 0; j < 5; ++j) {
            digits[j] = encoded_str[i + j] - 33;
            if (digits[j] < 0 || digits[j] >= 85) {
                throw std::invalid_argument("Invalid character");
            }
        }

        uint32_t value = 0;
        for (uint8_t d : digits) {
            value = value * 85 + d;
        }

        std::vector<uint8_t> chunk(4);
        for (int j = 3; j >= 0; --j) {
            chunk[j] = value & 0xFF;
            value >>= 8;
        }

        result.insert(result.end(), chunk.begin(), chunk.end());
        i += 5;
    }

    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return result;
}
