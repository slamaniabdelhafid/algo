#pragma once
#include <string>
#include <stdexcept>  // Add this for std::runtime_error

namespace ascii85 {
    std::string encode(const std::string& data);
    std::string decode(const std::string& data);
}
