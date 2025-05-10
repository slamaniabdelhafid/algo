#include "shannon_fano.hpp"
#include <algorithm>
#include <numeric>

void assign_codes(
    const std::vector<std::pair<uint8_t, size_t>>& symbols,
    CodeDict& codes,
    const std::string& code = ""
) {
    if (symbols.size() == 1) {
        codes[symbols[0].first] = code;
        return;
    }

    size_t total = 0;
    for (const auto& [sym, freq] : symbols) {
        total += freq;
    }

    size_t half = 0;
    size_t split_idx = 0;
    for (size_t i = 0; i < symbols.size(); ++i) {
        half += symbols[i].second;
        if (half >= total / 2) {
            split_idx = i;
            break;
        }
    }

    assign_codes(
        std::vector<std::pair<uint8_t, size_t>>(symbols.begin(), symbols.begin() + split_idx + 1),
        codes,
        code + "0"
    );
    assign_codes(
        std::vector<std::pair<uint8_t, size_t>>(symbols.begin() + split_idx + 1, symbols.end()),
        codes,
        code + "1"
    );
}

CodeDict shannon_fano_codes(const std::map<uint8_t, size_t>& freq) {
    std::vector<std::pair<uint8_t, size_t>> symbols(freq.begin(), freq.end());
    std::sort(symbols.begin(), symbols.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    CodeDict codes;
    assign_codes(symbols, codes);
    return codes;
}
