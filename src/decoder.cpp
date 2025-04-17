#include "ascii85.h"

std::vector<uint8_t> decode(const std::string& encoded) {
    std::vector<uint8_t> result;
    size_t i = 0;

    // Удаляем <~ и ~>
    if (encoded.size() >= 2 && encoded.substr(0, 2) == "<~") {
        i = 2;
    }
    if (encoded.size() >= 2 && encoded.substr(encoded.size() - 2, 2) == "~>") {
        encoded = encoded.substr(0, encoded.size() - 2);
    }

    while (i < encoded.size()) {
        if (encoded[i] == 'z') {
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            ++i;
            continue;
        }

        if (encoded.size() - i < 5) {
            throw std::invalid_argument("Invalid input length");
        }

        std::vector<uint8_t> digits(5);
        for (size_t j = 0; j < 5; ++j) {
            digits[j] = encoded[i + j] - 33;
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

    // Удаляем лишние нули
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return result;
}
