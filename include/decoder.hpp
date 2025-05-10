#pragma once
#include <string>
#include <cstdint> // Added for uint8_t

void decode_file(
    const std::string& compressed_path,
    const std::string& dict_path,
    const std::string& output_path
);
