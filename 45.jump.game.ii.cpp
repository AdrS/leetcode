#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
// Dynamic programming solution
int jump(vector<int>& nums) {
	// numJumps[i] = minimum number of jumps to get to position i
	vector<int> numJumps(nums.size(), INT_MAX);
	numJumps[0] = 0;
	for(int i = 0; i < nums.size(); ++i) {
		// position unreachable -> don't bother
		if(numJumps[i] == INT_MAX) {
			continue;
		}
		// if jump can get you to end, then done
		if(nums[i] + i >= nums.size() - 1) {
			if(nums.size() > 1) {
				return numJumps[i] + 1;
			} else {
				return 0;
			}
		}
		int lim = min(nums[i], (int)nums.size() - i - 1);
		for(int j = 1; j <= lim; ++j) {
			numJumps[i + j] = min(numJumps[i + j], numJumps[i] + 1);
		}
	}
	return numJumps.back();
} */

int jump(vector<int>& nums) {
	// TODO: see if I can get rid of some of these
	if(nums.size() <= 1) {
		return 0;
	// See if we can make in in one jump
	} else if(nums[0] >= (int)nums.size() - 1) {
		return 1;
	}

	// O(n)
	vector<int> numJumps(nums.size(), INT_MAX);
	numJumps[0] = 0;

	// Mark endpoint of range from first num
	numJumps[nums[0]] = 1;

	// Minimum number of jumps we definitely have to take
	int nj = 1;
	// Invariant: numJumps[j] = minimum number of jumps
	// to get nums[j] for 0 <= j < i
	//
	// Invariant: nj = minimum number of jumps to get to nums[i]
	// If numJumps[j] <= nj for j < i
	// Then num jumps to get to nums[k] for k <= j
	// is <= numJumps[j]
	for(int i = 1; i < nums.size(); ++i) {
		assert(numJumps[i - 1] <= nj);
		assert(nj <= numJumps[i]);

		// See if end is within range now
		if(i + nums[i] >= nums.size() - 1) {
			return nj + 1;
		}

		// Mark upper end of range of numbers we can jump to from here
		// Don't overwrite markers for shorter route
		if(numJumps[i + nums[i]] == INT_MAX) {
			numJumps[i + nums[i]] = nj + 1;
		}

		// We found the marker for the end of a jump range
		if(numJumps[i] == nj) {
			// Looks like we have to take another jump
			nj++;
		} else {
			// nums[i] is within range of on of the previous
			// numbers
			numJumps[i] = nj;
		}
	}
	return numJumps.back();

	// num jumps
	// ------------------------------------------
	// 0  inf inf inf inf inf inf nums[0] inf inf
	// nj = 0
	//
	// 0  1 inf nums[1] inf inf inf nums[0] inf inf
	// nj = 1
	//
	// 0  1 1 nums[1] inf nums[2] inf nums[0] inf inf
	// nj = 1
	//
	// 0  1 1 1 inf nums[2] inf nums[0] inf nums[3]
	// nj = 1
	//
	// start, range

/*
	[2,3,1,1,4]
	2
	0, <=1, <=1, ?, ?
	2 3
	0, 1, <=1, <=2, <=2

	[1,2,100,1,1,1,1,1,1]
	1
	0, <=1, ?, ?, ?, ?, ?, ?, ? 
	1 2
	0, 1, <=2, <=2, ?, ?, ?, ?, ? 
	1 2 100
	0, 1, 2, <=2, <=3, <=3, <=3, <=3, <=3,
*/
}

struct TestCase {
	vector<int> nums;
	int expected;
};

void runTestCase(vector<int> &nums, int expected) {
	int got = jump(nums);
	if(got != expected) {
		cerr << "jump([ ";
		for(int n : nums) {
			cerr << n << " ";
		}
		cerr << "]) returned " << got << " expected "
			<< expected << endl;
	}
}

int main() {
	vector<TestCase> testCases = {
		{{2,3,1,1,4}, 2},
		{{4,3,1,1,4}, 1},
		{{1,1,1,1,4}, 4},
		{{1,2,100,1,1,1,1,1,1}, 3},
		{{4}, 0},
	};

	vector<int> large(500);
	iota(large.rbegin(), large.rend(), 1);
	large.push_back(1);
	large.push_back(0);
	testCases.push_back({large, 2});

	for(auto &testCase : testCases) {
		runTestCase(testCase.nums, testCase.expected);
	}
	return 0;
}
