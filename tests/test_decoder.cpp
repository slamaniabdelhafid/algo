#include "decoder.hpp"
#include <cassert>
#include <fstream>
#include <vector>

void test_decoder_with_precomputed() {
    // Create test compressed file and dictionary
    std::ofstream dict("precomputed_dict.json");
    dict << R"({"65":"0","66":"10","67":"110"})";
    dict.close();

    // Binary for "0 10 10 110 110 110" (ABBCCC)
    std::ofstream compressed("precomputed.bin", std::ios::binary);
    compressed.put(0b01010110);
    compressed.put(0b11011000); // Last 3 bits are padding
    compressed.close();

    // Decode
    decode_file("precomputed.bin", "precomputed_dict.json", "decoded.bin");

    // Verify
    std::ifstream in("decoded.bin", std::ios::binary);
    std::vector<uint8_t> decoded_data(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    );
    assert(decoded_data == std::vector<uint8_t>{'A', 'B', 'B', 'C', 'C', 'C'});
}

int main() {
    test_decoder_with_precomputed();
    return 0;
}
