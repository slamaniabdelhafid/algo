#include <iostream>
#include "ascii85.h"
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 2 || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0)) {
        std::cerr << "Usage: " << argv[0] << " [-e|-d]" << std::endl;
        return 1;
    }

    std::string input;
    std::getline(std::cin, input);

    try {
        if (strcmp(argv[1], "-e") == 0) {
            std::vector<uint8_t> data(input.begin(), input.end());
            std::cout << encode(data);
        } else {
            std::vector<uint8_t> decoded = decode(input);
            std::cout.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
