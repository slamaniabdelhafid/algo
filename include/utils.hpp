#pragma once
#include <map>
#include <string>
#include <fstream>
#include <cstdint>

// Define a simple JSON replacement if we can't use nlohmann
namespace nlohmann {
    using json = std::map<std::string, std::string>;
}

void save_dictionary(const std::map<uint8_t, std::string>& codes, const std::string& file_path);
std::map<uint8_t, std::string> load_dictionary(const std::string& file_path);
