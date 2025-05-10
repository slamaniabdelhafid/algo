#pragma once
#include <map>
#include <vector>
#include <cstdint>

std::map<uint8_t, size_t> build_frequency_table(const std::vector<uint8_t>& data);
