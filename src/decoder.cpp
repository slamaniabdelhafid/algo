#include "decoder.hpp"
#include "utils.hpp"
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <cstdint>

std::string read_compressed(const std::string& path, uint32_t& bit_length) {
    std::ifstream file(path, std::ios::binary);
    
    // Read original bit length
    file.read(reinterpret_cast<char*>(&bit_length), sizeof(bit_length));
    
    // Read compressed bits
    std::string bit_string;
    char byte;
    while (file.get(byte)) {
        bit_string += std::bitset<8>(byte).to_string();
    }
    
    // Trim to original length
    if (bit_string.size() > bit_length) {
        bit_string.resize(bit_length);
    }
    
    return bit_string;
}

void decode_file(const std::string& compressed_path,
                const std::string& dict_path,
                const std::string& output_path) {
    uint32_t bit_length;
    auto bit_string = read_compressed(compressed_path, bit_length);
    auto codes = load_dictionary(dict_path);
    
    std::unordered_map<std::string, uint8_t> reverse_codes;
    for (const auto& [sym, code] : codes) {
        reverse_codes[code] = sym;
    }
    
    std::vector<uint8_t> output;
    std::string current_code;
    
    for (char bit : bit_string) {
        current_code += bit;
        if (reverse_codes.count(current_code)) {
            output.push_back(reverse_codes[current_code]);
            current_code.clear();
        }
    }
    
    std::ofstream out(output_path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(output.data()), output.size());
}
