#include "utils.hpp"
#include <iostream>

void save_dictionary(const std::map<uint8_t, std::string>& codes, const std::string& file_path) {
    std::ofstream file(file_path);
    for (const auto& [sym, code] : codes) {
        file << static_cast<int>(sym) << ":" << code << "\n";
    }
}

std::map<uint8_t, std::string> load_dictionary(const std::string& file_path) {
    std::ifstream file(file_path);
    std::map<uint8_t, std::string> codes;
    std::string line;
    
    while (std::getline(file, line)) {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            int sym = std::stoi(line.substr(0, colon_pos));
            std::string code = line.substr(colon_pos + 1);
            codes[static_cast<uint8_t>(sym)] = code;
        }
    }
    
    return codes;
}
