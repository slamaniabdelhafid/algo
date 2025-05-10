#include "decoder.hpp"
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>

void test_decoder_with_precomputed() {
    // Create test compressed file and dictionary
    std::ofstream dict("precomputed_dict.txt");
    dict << "65:0\n66:10\n67:110\n";  // A:0, B:10, C:110
    dict.close();

    // Binary for "0 10 10 110 110 110" (ABBCCC)
    // With 2 padding bits (total 16 bits: 01010110 11011000)
    std::ofstream compressed("precomputed.bin", std::ios::binary);
    uint32_t bit_length = 14; // 6 symbols: A(1) + B(2) + B(2) + C(3) + C(3) + C(3)
    compressed.write(reinterpret_cast<const char*>(&bit_length), sizeof(bit_length));
    compressed.put(0b01010110); // First byte
    compressed.put(0b11011000); // Second byte with padding
    compressed.close();

    // Decode
    decode_file("precomputed.bin", "precomputed_dict.txt", "decoded.bin");

    // Verify
    std::ifstream in("decoded.bin", std::ios::binary);
    std::vector<uint8_t> decoded_data{
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    };
    
    const std::vector<uint8_t> expected{'A', 'B', 'B', 'C', 'C', 'C'};
    
    if (decoded_data != expected) {
        std::cerr << "Test failed!\n";
        std::cerr << "Expected: ";
        for (auto b : expected) std::cerr << (int)b << " ";
        std::cerr << "\nGot: ";
        for (auto b : decoded_data) std::cerr << (int)b << " ";
        std::cerr << "\n";
        assert(false);
    }
    
    std::cout << "Decoder test passed successfully!\n";
}

int main() {
    test_decoder_with_precomputed();
    return 0;
}
