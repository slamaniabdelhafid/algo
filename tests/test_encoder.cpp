#include "encoder.hpp"
#include "decoder.hpp"
#include <cassert>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream> // For better error reporting

void test_encode_decode() {
    // Create test file
    std::vector<uint8_t> test_data = {'A', 'B', 'B', 'C', 'C', 'C'};
    std::string input_path = "test_input.bin";
    std::ofstream out(input_path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(test_data.data()), test_data.size());
    out.close();

    // Test encode/decode
    encode_file(input_path, "compressed.bin", "dict.txt");
    decode_file("compressed.bin", "dict.txt", "output.bin");

    // Verify
    std::ifstream in("output.bin", std::ios::binary);
    std::vector<uint8_t> decoded_data{
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    };
    
    if (decoded_data.size() != test_data.size()) {
        std::cerr << "Size mismatch! Original: " << test_data.size() 
                  << ", Decoded: " << decoded_data.size() << "\n";
        assert(false);
    }
    
    for (size_t i = 0; i < decoded_data.size(); ++i) {
        if (decoded_data[i] != test_data[i]) {
            std::cerr << "Mismatch at position " << i 
                      << ": Original=" << test_data[i] 
                      << ", Decoded=" << decoded_data[i] << "\n";
            assert(false);
        }
    }
    
    std::cout << "Encoder test passed successfully!\n";
}

int main() {
    test_encode_decode();
    return 0;
}
