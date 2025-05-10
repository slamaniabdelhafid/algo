#pragma once
#include <map>
#include <string>
#include <cstdint>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void save_dictionary(
    const std::map<uint8_t, std::string>& codes,
    const std::string& file_path
);

std::map<uint8_t, std::string> load_dictionary(
    const std::string& file_path
);
