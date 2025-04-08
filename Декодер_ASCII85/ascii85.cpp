#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

std::vector<uint8_t> decode(const std::string& encoded) {
    std::vector<uint8_t> result;
    size_t i = 0;
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

        // Read 5 characters
        std::vector<uint8_t> digits(5);
        for (size_t j = 0; j < 5; ++j) {
            digits[j] = encoded[i + j] - 33;
            if (digits[j] < 0 || digits[j] >= 85) {
                throw std::invalid_argument("Invalid character");
            }
        }

        // Compute 32-bit value
        uint32_t value = 0;
        for (uint8_t d : digits) {
            value = value * 85 + d;
        }

        // Convert to 4 bytes
        std::vector<uint8_t> chunk(4);
        for (int j = 3; j >= 0; --j) {
            chunk[j] = value & 0xFF;
            value >>= 8;
        }

        result.insert(result.end(), chunk.begin(), chunk.end());
        i += 5;
    }

    // Remove trailing zeros from padding
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    try {
        std::vector<uint8_t> decoded = decode(input);
        std::cout.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
