#pragma once
#include <map>
#include <string>
#include <cstdint>
#include <vector>
#include <utility>

using CodeDict = std::map<uint8_t, std::string>;

CodeDict shannon_fano_codes(const std::map<uint8_t, size_t>& freq);
