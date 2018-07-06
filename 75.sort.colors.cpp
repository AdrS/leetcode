#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int> &nums) {
	cout << '[';
	if(!nums.empty()) {
		cout << nums[0];
	}
	for(int i = 1; i < nums.size(); ++i) {
		cout << ", " << nums[i];
	}
	cout << ']' << endl;
}

void sortColors(vector<int>& nums) {
	// 0 ... 0 1 ... 1 2 ... 2 x ? ? ?
	
	// Index of element after the last red
	int redEnd = 0;
	int whiteEnd = 0;
	
	// 0,0,1,2
	
	// Invariants: [0, redEnd) is red, [redEnd, whiteEnd) is white, and [whiteEnd, blueEnd) is blue
	for(int blueEnd = 0; blueEnd < nums.size(); ++blueEnd) {
		if(nums[blueEnd] == 0) {
			swap(nums[redEnd], nums[blueEnd]);
			if(redEnd != whiteEnd) {
				swap(nums[whiteEnd], nums[blueEnd]);
			}
			++whiteEnd;
			++redEnd;
		} else if(nums[blueEnd] == 1) {
			swap(nums[whiteEnd], nums[blueEnd]);
			++whiteEnd;
		}
	}
}

int main() {
	vector<int> nums = {1,2,0,0};
	sortColors(nums);
	printVector(nums);
	return 0;
}
