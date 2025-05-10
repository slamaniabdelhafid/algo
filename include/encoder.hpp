#pragma once
#include <string>
#include <cstdint> // Added for uint8_t

void encode_file(
    const std::string& input_path,
    const std::string& output_path,
    const std::string& dict_path
);
