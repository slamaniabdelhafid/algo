#include "ascii85.h"
#include <iostream>
#include <iterator>  // Add this for std::istreambuf_iterator

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [-e|-d]\n";
        return 1;
    }

    std::string input(std::istreambuf_iterator<char>(std::cin), {});
    
    try {
        if (std::string(argv[1]) == "-e") {
            std::cout << ascii85::encode(input);
        } 
        else if (std::string(argv[1]) == "-d") {
            std::cout << ascii85::decode(input);
        } 
        else {
            std::cerr << "Invalid mode. Use -e (encode) or -d (decode)\n";
            return 1;
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
