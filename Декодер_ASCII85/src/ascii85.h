#pragma once
#include <vector>
#include <string>

std::string encode(const std::vector<uint8_t>& data);
std::vector<uint8_t> decode(const std::string& encoded);
