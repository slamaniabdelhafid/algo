#include "encoder.hpp"
#include "frequency_table.hpp"
#include "shannon_fano.hpp"
#include "utils.hpp"
#include <fstream>
#include <bitset>
#include <vector>
#include <cstdint>

std::vector<uint8_t> read_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    return std::vector<uint8_t>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

void write_compressed(const std::string& bit_string, const std::string& output_path) {
    std::ofstream out(output_path, std::ios::binary);
    
    // Write original bit length (4 bytes)
    uint32_t bit_length = bit_string.size();
    out.write(reinterpret_cast<const char*>(&bit_length), sizeof(bit_length));
    
    // Write padded bits
    size_t padding = (8 - (bit_length % 8)) % 8;
    std::string padded = bit_string + std::string(padding, '0');
    
    for (size_t i = 0; i < padded.size(); i += 8) {
        std::bitset<8> bits(padded.substr(i, 8));
        out.put(static_cast<char>(bits.to_ulong()));
    }
}

void encode_file(const std::string& input_path, 
                const std::string& output_path,
                const std::string& dict_path) {
    auto data = read_file(input_path);
    auto freq = build_frequency_table(data);
    auto codes = shannon_fano_codes(freq);
    
    std::string bit_string;
    for (uint8_t byte : data) {
        bit_string += codes[byte];
    }
    
    write_compressed(bit_string, output_path);
    save_dictionary(codes, dict_path);
}
