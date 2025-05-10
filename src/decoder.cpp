#include "decoder.hpp"
#include "utils.hpp"
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <vector>  // Added for std::vector
#include <cstdint> // Added for uint8_t

std::string read_compressed(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::string bit_string;
    
    char byte;
    while (file.get(byte)) {
        bit_string += std::bitset<8>(byte).to_string();
    }
    
    return bit_string;
}

void decode_file(
    const std::string& compressed_path,
    const std::string& dict_path,
    const std::string& output_path
) {
    auto codes = load_dictionary(dict_path);
    std::unordered_map<std::string, uint8_t> reverse_codes;
    for (const auto& [sym, code] : codes) {
        reverse_codes[code] = sym;
    }
    
    std::string bit_string = read_compressed(compressed_path);
    std::vector<uint8_t> output;
    std::string current_code;
    
    for (char bit : bit_string) {
        current_code += bit;
        if (reverse_codes.find(current_code) != reverse_codes.end()) {
            output.push_back(reverse_codes[current_code]);
            current_code.clear();
        }
    }
    
    std::ofstream out(output_path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(output.data()), output.size());
}
