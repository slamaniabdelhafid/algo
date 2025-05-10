#include "utils.hpp"
#include <iostream>

void save_dictionary(const std::map<uint8_t, std::string>& codes, const std::string& file_path) {
    json j;
    for (const auto& [sym, code] : codes) {
        j[std::to_string(sym)] = code;
    }
    
    std::ofstream file(file_path);
    file << j.dump(4);
}

std::map<uint8_t, std::string> load_dictionary(const std::string& file_path) {
    std::ifstream file(file_path);
    json j;
    file >> j;
    
    std::map<uint8_t, std::string> codes;
    for (auto& [sym_str, code] : j.items()) {
        codes[static_cast<uint8_t>(std::stoi(sym_str))] = code;
    }
    
    return codes;
}
