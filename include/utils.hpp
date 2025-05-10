#pragma once
#include <map>
#include <string>
#include <fstream>
#include <cstdint>
#include <sstream>

// Simple dictionary serialization without JSON
void save_dictionary(const std::map<uint8_t, std::string>& codes, const std::string& file_path);
std::map<uint8_t, std::string> load_dictionary(const std::string& file_path);
