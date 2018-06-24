#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Go to state ni
// If p[ni] == '*', then we can automatically
// get to state ni + 1.
// We can keep on going forward while the 
// pattern is * chars
void advance(vector<bool> &pos, string &p, int ni) {
	pos[ni] = true;
	int j = 0;
	while(p[ni + j] == '*' && ni + j < pos.size() - 1) {
		pos[ni + j + 1] = true;
		++j;
	}
}

bool isMatch(string s, string p) {
	// Empty string
	if(s.empty()) {
		// only patterns that match empty string are
		// "","*","**",...
		for(char c : p) {
			if(c != '*') return false;
		}
		return true;
	}
	
	// Empty pattern
	if(p.empty()) {
		//only string fully matched by empty pattern is empty string
		return false;
	}

	// Store where in pattern we could be
	vector<bool> curPos(p.size() + 1);
	advance(curPos, p, 0);
	for(char c : s) {
		vector<bool> nextPos(p.size() + 1);
		
		// Stop early if curPos has nothing
		// ie: were there any possible state transitions?
		bool didSomething = false;

		for(int i = 0; i < p.size(); ++i) {
			if(!curPos[i]) {
				continue;
			}
			didSomething = true;

			// Match any character
			if(p[i] == '?') {
				advance(nextPos, p, i + 1);
			} else if(p[i] == '*') {
				// Match character with wildcard
				advance(nextPos, p, i);
			} else if(p[i] == c) {
				// Matches, so we can advance
				advance(nextPos, p, i + 1);
			}
		}
		if(!didSomething) return false;

		// nextPos is about to go out of scope and be reset on
		// the next loop iteration
		swap(curPos, nextPos);
	}
	// See if any of the paths thought the FSM ended
	return curPos.back();
}
/*
bool isMatch(const char *s, const char *p) {
	// empty pattern only matches empty string
	if(!p[0]) return !s[0];
	// empty string only matched by "" and wildcard(s)
	if(!s[0]) {
		while(*p) {
			if(*p != '*') return false;
			++p;
		}
		return true;
	}

	if(p[0] == '?') {
		return isMatch(s + 1, p + 1);
	} else if(p[0] == '*') {
		// consume character
		// end wildcard match, or match another letter
		return isMatch(s, p + 1) || isMatch(s + 1, p);
	} else {
		return p[0] == s[0] && isMatch(s + 1, p + 1);
	}
} */

struct TestCase {
	string text;
	string pattern;
	bool isMatch;
};

int main() {
	// supposedly dynamic programming is better
	//assert(isMatch("aa","a") == false);
	//assert(isMatch("aa","aa") == true);
	//assert(isMatch("aaa","aa") == false);
	//assert(isMatch("aa", "*") == true);
	//assert(isMatch("aa", "a*") == true);
	//assert(isMatch("ab", "?*") == true);
	//assert(isMatch("aab", "c*a*b") == false);
	// string, pattern, is match?
	TestCase testCases[] = {
		{"mississippi", "m??*ss*?i*pi", false},
		{"aa", "a", false},
		{"aa", "a*", true},
		{"cb", "?a", false},
		{"abceb", "*a*b", true},
		{"acdcb", "a*c?b", false},
		{"mississippi", "mis*is*p*?", true},
		{"abc", "bc", false},
		{"abcd", "abcd", true},
		{"ac", "?c", true},
		{"ac", "a?d", false},
		{"abc", "*", true},
		{"abc", "a*", true},
		{"abc", "*d", false},
		{"abc", "?*", true},
		{"abc", ".*.", false},
		{"abc", "*b*", true},
		{"", "ad", false},
		{"as", "", false},
		{"", "", true},
		{"", "****", true},
		{"abc", "***", true},
		{"a", "a*", true},
		{"a", "a***", true},
		{"a", "?*", true}
	};
	for(auto &tc : testCases) {
		bool got = isMatch(tc.text, tc.pattern);
		if(got != tc.isMatch) {
			cerr << "isMatch(\"" << tc.text << "\", \"" << tc.pattern << "\") got " << got << " expected " << tc.isMatch << endl;
		}
	}
	return 0;
}
