#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

string largestNumber(vector<int>& nums) {
	// Q: Is this the same as sorting based on lexographical order?
	// A: No. "9", "95", "8" becomes "8", "9", "95" in lexographic order. We want "8", "95", "9"
	// ie: break ties by putting longest first
	// sort based on highest order digit
	// break ties based on 2nd highest order digit
	// and so on
	if(nums.empty()) return "";

	vector<string> numStrs;
	for(int n : nums) {
		numStrs.push_back(to_string(n));
	}
	stable_sort(numStrs.begin(), numStrs.end(), [](const string &a, const string &b) -> bool {
		/*
		int i = 0;
		while(i < (int)a.size() && i < (int)b.size()) {
			if(a[i] > b[i]) return true;
			if(a[i] < b[i]) return false;
			++i;
		}
		// the logic here does not work
		// Favor prefixes (they give more flexibility)
		return i == (int)a.size();
		*/
		return a + b > b + a;
	});
	if(numStrs[0] == "0") return "0";
	string largestNumber;
	for(auto &s : numStrs) {
		largestNumber.append(s);
	}
	//cout << largestNumber << endl;
	return largestNumber;
}
struct TestCase {
	vector<int> nums;
	string expected;
};

int main() {
	TestCase testCases[] = {
		{{10,2}, "210"},
		{{10,20}, "2010"},
		{{3,30, 34, 5, 9}, "9534330"},
		{{10, 11, 20, 9}, "9201110"},
		{{100, 10, 1000}, "101001000"},
		{{100, 10, 1000, 0}, "1010010000"},
		{{9, 95, 8}, "9958"},
		{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
		{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, "0"}
	};
	for(auto &testCase : testCases) {
		string got = largestNumber(testCase.nums);
		if(got != testCase.expected) {
			cout << "largestNumber([";
			for(auto n : testCase.nums) {
				cout << n << ", ";
			}
 			cout << "]) -> " << got << " expected " << testCase.expected << endl;
		}
	}
	return 0;
}

