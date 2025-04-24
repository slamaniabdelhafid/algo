#include "ascii85.h"
#include <vector>
#include <stdexcept>
#include <cctype>
#include <string>

namespace ascii85 {

std::string decode_ascii85_to_string(const std::string& input_raw) {
    std::string input = input_raw;
    if (input.size() >= 2 && input.substr(0, 2) == "<~") {
        input = input.substr(2);
    }
    if (input.size() >= 2 && input.substr(input.size() - 2) == "~>") {
        input = input.substr(0, input.size() - 2);
    }

    std::vector<char> group;
    std::string output;
    uint32_t value = 0;

    for (char ch : input) {
        if (std::isspace(static_cast<unsigned char>(ch))) continue;

        if (ch == 'z') {
            if (!group.empty()) throw std::runtime_error("'z' inside group");
            output.append(4, '\0');
            continue;
        }

        if (ch < '!' || ch > 'u') throw std::runtime_error("Invalid character in ASCII85");

        group.push_back(ch);
        if (group.size() == 5) {
            value = 0;
            for (char c : group) {
                value = value * 85 + (c - 33);
            }
            for (int i = 3; i >= 0; --i)
                output += static_cast<char>((value >> (i * 8)) & 0xFF);
            group.clear();
        }
    }

    if (!group.empty()) {
        int padding = 5 - group.size();
        for (int i = 0; i < padding; ++i)
            group.push_back('u');

        value = 0;
        for (char c : group)
            value = value * 85 + (c - 33);

        for (int i = 3; i >= 0; --i)
            if (i >= padding)
                output += static_cast<char>((value >> (i * 8)) & 0xFF);
    }

    return output;
}

} 
