#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void checkNumOccurancesInvariants(int numOccurances[256], int numCharsLeft, string t) {
	int numLeft = 0;
	for(int i = 0; i < 256; ++i) {
		if(numOccurances[i] == 0) {
			++numLeft;
		}
	}
	assert(numCharsLeft == numLeft);
	for(auto c : t) {
		assert(numOccurances[c] >= 0);
	}

}

string minWindow(string s, string t) {
	if(s.size() < t.size()) {
		return "";
	}

	// number of times character appears in window
	vector<int> numOccurances(256, 0);
	// number of times character is needed
	vector<int> needed(256, 0);

	// number of chars in t left
	int numCharsLeft = 0;
	for(auto c : t) {
		if(!needed[c]) {
			++numCharsLeft;
		}
		++needed[c];
	}

	// initialize for first window
	int windowStart = 0;
	int windowEnd = t.size();
	for(int i = 0; i < t.size(); ++i) {
		// character not in t
		if(!needed[s[i]]) {
			continue;
		}
		++numOccurances[s[i]];
		if(numOccurances[s[i]] == needed[s[i]]) {
			--numCharsLeft;
		}
	}

	// keep track of narrowest window
	int bestStart = 0;
	int narrowestWidth = numCharsLeft == 0;

	if(!numCharsLeft) {
		return s.substr(0, t.size());
	}

	// expand right side of winow until all chars in t are covered
	while(windowEnd < s.size()) {
		if(needed[s[windowEnd]]) {
			++numOccurances[s[windowEnd]];
			if(numOccurances[s[windowEnd]] == needed[s[windowEnd]]) {
				--numCharsLeft;
				if(!numCharsLeft) {
					// contract left side of winow as long as all chars are covered
					do {
						if(!needed[s[windowStart]]) {
							++windowStart;
							continue;
						}
						// check if we are about to go to not enought occurances in window
						if(numOccurances[s[windowStart]] == needed[s[windowStart]]) {
							++numCharsLeft;
						}
						--numOccurances[s[windowStart]];
						++windowStart;
					} while(!numCharsLeft);
					int width = windowEnd - windowStart + 2;
					if(width < narrowestWidth || !narrowestWidth) {
						narrowestWidth = width;
						bestStart = windowStart - 1;
					}
				}
			}

		}
		++windowEnd;            
	}
	return s.substr(bestStart, narrowestWidth);
}

struct TestCase {
	string s;
	string t;
	string expected;
};

int main() {
	TestCase testCases[] = {
		{"ADOBECODEBANC", "ABC", "BANC"},
		{"AMANAPLANACANALPANAMA", "MAP", "MANAP"},
		{"AMANAPLANACANALPANAMA", "MAR", ""},
		{"AMANAPLANACANALPACNAMA", "CAP", "PAC"},
		{"a", "a", "a"},
		{"ab", "ba", "ab"},
		{"captain", "captain", "captain"},
		{"bbaa", "aba", "baa"}
	};

	for(int i = 0; i < sizeof(testCases)/sizeof(TestCase); ++i) {
		string got = minWindow(testCases[i].s, testCases[i].t);
		if(got != testCases[i].expected) {
			cerr << "minWindow(\"" <<
				testCases[i].s << "\", \"" <<
				testCases[i].t << "\") returned \""<<
				got << "\" expected \"" << testCases[i].expected << "\"" << endl;

		}
	}
	return 0;
}

