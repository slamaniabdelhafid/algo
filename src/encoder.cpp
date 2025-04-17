#include "ascii85.h"
#include <cstdint>
#include <vector>

std::string encode(const std::vector<uint8_t>& data) {
    std::string result;
    size_t i = 0;
    while (i < data.size()) {
        std::vector<uint8_t> chunk(4, 0);
        size_t chunk_size = std::min(data.size() - i, static_cast<size_t>(4)); // Исправлено
        std::copy(data.begin() + i, data.begin() + i + chunk_size, chunk.begin());
        i += chunk_size;

        uint32_t value = 0;
        for (size_t j = 0; j < 4; ++j) {
            value = (value << 8) | chunk[j];
        }

        if (value == 0 && chunk_size == 4) {
            result += 'z';
            continue;
        }

        std::vector<uint8_t> digits(5);
        for (int j = 4; j >= 0; --j) {
            digits[j] = value % 85;
            value /= 85;
        }

        for (uint8_t d : digits) {
            result += static_cast<char>(d + 33);
        }
    }

    if (data.size() % 4 != 0) {
        size_t pad = 4 - (data.size() % 4);
        result.erase(result.size() - pad, pad);
    }

    return result;
}
