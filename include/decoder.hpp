#pragma once
#include <string>

void decode_file(
    const std::string& compressed_path,
    const std::string& dict_path,
    const std::string& output_path
);
