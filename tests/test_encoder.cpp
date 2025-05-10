#include "encoder.hpp"
#include "decoder.hpp"
#include <cassert>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>

void test_encode_decode() {
    // Test data
    std::vector<uint8_t> test_data = {'A', 'B', 'B', 'C', 'C', 'C'};
    std::string input_path = "test_input.bin";
    std::string compressed_path = "compressed.bin";
    std::string dict_path = "dict.txt";
    std::string output_path = "output.bin";

    // Create test file
    std::ofstream out(input_path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(test_data.data()), test_data.size());
    out.close();

    // Encode and decode
    encode_file(input_path, compressed_path, dict_path);
    decode_file(compressed_path, dict_path, output_path);

    // Verify
    std::ifstream in(output_path, std::ios::binary);
    std::vector<uint8_t> decoded_data(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    );

    // Debug output
    std::cout << "Original size: " << test_data.size() 
              << ", Decoded size: " << decoded_data.size() << "\n";
              
    if (decoded_data != test_data) {
        std::cerr << "Mismatch found!\n";
        std::cerr << "Original: ";
        for (auto b : test_data) std::cerr << (int)b << " ";
        std::cerr << "\nDecoded: ";
        for (auto b : decoded_data) std::cerr << (int)b << " ";
        std::cerr << "\n";
        assert(false);
    }
    
    std::cout << "Test passed successfully!\n";
}

int main() {
    test_encode_decode();
    return 0;
}
