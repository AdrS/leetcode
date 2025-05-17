#include <string>
#include <unordered_set>

std::unordered_set<std::string> powersOfTwoDigits = {
"1",
"2",
"4",
"8",
"16",
"23",
"46",
"128",
"256",
"125",
"0124",
"0248",
"0469",
"1289",
"13468",
"23678",
"35566",
"011237",
"122446",
"224588",
"0145678",
"0122579",
"0134449",
"0368888",
"11266777",
"23334455",
"01466788",
"112234778",
"234455668",
"012356789"
};

class Solution {
public:
    // Precomputation
    bool reorderedPowerOf2(int n) {
        return powersOfTwoDigits.contains(sortedDigits(n));
    }
    
    // No precomputation
    bool reorderedPowerOf2V1(int n) {
        std::string nDigits = sortedDigits(n);
        for (int i = 1; i <= 1'000'000'000; i *= 2) {
            if (nDigits == sortedDigits(i)) {
                return true;
            }
        }
        return false;
    }
    std::string sortedDigits(int n) {
        std::string digits = std::to_string(n);
        std::sort(digits.begin(), digits.end());
        return digits;
    }
};
