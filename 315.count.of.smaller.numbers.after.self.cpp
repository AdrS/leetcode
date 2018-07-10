#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

vector<int> countSmallerSlow(vector<int>& nums) {
	vector<int> counts(nums.size());
	for(int i = 0; i < nums.size(); ++i) {
		int count = 0;
		for(int j = i + 1; j < nums.size(); ++j) {
			if(nums[i] > nums[j]) {
				++count;
			}
		}
		counts[i] = count;
	}
	return counts;
}

vector<int> countSmaller(vector<int>& nums) {
	vector<int> counts(nums.size());
	return counts;
}

int main() {
	vector<vector<int>> tests = {
		{5,2,6,1},
		{5,2,2, 6,5, 1}
	};
	for(int i = 0; i < tests.size(); ++i) {
		auto expected = countSmallerSlow(tests[i]);
		auto got = countSmaller(tests[i]);
		assert(expected.size() == tests[i].size());
		if(got.size() != tests[i].size()) {
			cerr << "Test " << i + 1 << " result has size " << got.size() << " not " << tests[i].size() << endl;
			continue;
		}
		for(int j = 0; j < got.size(); ++j) {
			if(expected[j] != got[j]) {
				for(int k = 0; k < expected.size(); ++k) {
					cerr << expected[k] << ", ";
				}
				cerr << " != ";
				for(int k = 0; k < got.size(); ++k) {
					cerr << got[k] << ", ";
				}
				cerr << endl;
				break;
			}
		}
	}
	return 0;
}

