#include "frequency_table.hpp"
#include <map>

std::map<uint8_t, size_t> build_frequency_table(const std::vector<uint8_t>& data) {
    std::map<uint8_t, size_t> freq;
    for (uint8_t byte : data) {
        freq[byte]++;
    }
    return freq;
}
