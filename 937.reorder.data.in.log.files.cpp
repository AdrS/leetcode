#include <string>
#include <string_view>
#include <cctype>
#include <vector>

using ::std::vector;
using ::std::string;

// This assumes the log line has more than just an identifier.
// If the log line has only an identifier, then it could be either
// a letter or digit log.
bool isDigitLog(const std::string& line) {
    return std::isdigit(line.back());
}

std::pair<std::string_view, std::string_view> split_log(std::string_view line) {
    // Assumes there is a space after the identifier
    int i = line.find(' ');
    std::string_view identifier = line.substr(0, i);
    std::string_view contents = line.substr(i + 1);
    return {identifier, contents};
}

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        // The comparator returns whether lhs < rhs
        std::stable_sort(logs.begin(), logs.end(), [](const std::string& lhs, const std::string& rhs) {
            bool lhs_is_digit = isDigitLog(lhs);
            if (lhs_is_digit != isDigitLog(rhs)) {
                // Letter logs go befor digit logs
                return !lhs_is_digit;
            }
            // Maintain relative order of digit logs
            if (lhs_is_digit) {
                // Treat all digit logs as equal and rely on the stable sort to keep the relative ordering
                // Since they are all "equal" < is always false.
                return false;
            }
            // Split letter-logs into the identifier and contents
            auto [lhs_identifier, lhs_contents] = split_log(lhs);
            auto [rhs_identifier, rhs_contents] = split_log(rhs);
            // Sort based on the contents
            int c = lhs_contents.compare(rhs_contents);
            if (c < 0) {
                return true;
            } else if (c > 0) {
                return false;
            } else {
                // If contents are the same, then sort lexicographically by identifiers.
                return lhs_identifier < rhs_identifier;
            }
        });
        return logs;
    }
};
