#include "encoder.hpp"
#include "decoder.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  Encode: " << argv[0] << " encode <input> <compressed> <dict>\n"
                  << "  Decode: " << argv[0] << " decode <compressed> <dict> <output>\n";
        return 1;
    }

    std::string mode(argv[1]);
    if (mode == "encode" && argc == 5) {
        encode_file(argv[2], argv[3], argv[4]);
    } else if (mode == "decode" && argc == 5) {
        decode_file(argv[2], argv[3], argv[4]);
    } else {
        std::cerr << "Invalid arguments\n";
        return 1;
    }

    return 0;
}
