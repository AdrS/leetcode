#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word2.empty()) return word1.size();
        if(word1.empty()) return word2.size();

        // OPT[i][j] = minDistance(word1[0...i], word2[0...j])
        // OPT[0][j] = j
        // OPT[i][0] = i
        // if word1[i] == word2[j] then OPT[i][j] = OPT[i - 1][j - 1]
        // else
        //   OPT[i][j] = min(OPT[i - 1][j] + 1, OPT[i][j - 1] + 1, OPT[i - 1][j - 1] + 2)
        // else OPT[i][j] = min(OPT[i - 1]OPT[j], OPT[i]OPT[j - 1], OPT[i - 1]OPT[j - 1])
        vector<int> prev(word2.size() + 1);
        for(unsigned i = 0; i <= word2.size(); ++i) {
            prev[i] = i;
        }
        vector<int> cur(word2.size() + 1,0);
        for(unsigned i = 1; i <= word1.size(); ++i) {
            cur[0] = i;
            for(unsigned j = 1; j <= word2.size(); ++j) {
                if(word1[i - 1] == word2[j - 1]) {
                    cur[j] = prev[j - 1];
                } else {
                    cur[j] = min(cur[j - 1] + 1, prev[j] + 1);
                }
            }
            swap(prev, cur);
        }
        return prev.back();
    }
};
struct TestCase {
	string s1;
	string s2;
	int expected;
};

int main() {
	Solution s;
	TestCase testCases [] = {
		{"sea", "eat", 2},
		{"a", "b", 2},
		{"asdf", "", 4},
		{"", "asdff", 5},
		{"cabage", "aaf", 5}
	};
	for(auto &tc : testCases) {
		int got = s.minDistance(tc.s1, tc.s2);
		if(got != tc.expected) {
			cerr << "FAIL: minDistance(" << tc.s1 << ", " << tc.s2 << ") -> " << got << " expected " << tc.expected << endl;
		}
	}
	return 0;
}
