#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// backtracking solution
void aux(vector<vector<int>> &solutions, vector<int> &cur, int i, vector<int> &nums) {
	if(i == nums.size()) {
		solutions.push_back(cur);
	} else {
		// subsets without element
		aux(solutions, cur, i + 1, nums);

		// subsets with element
		cur.push_back(nums[i]);
		aux(solutions, cur, i + 1, nums);
		cur.pop_back();
	}
}

vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> solutions;
	vector<int> cur;
	aux(solutions, cur, 0, nums);
	return solutions;
}

int main() {
	vector<int> nums;

	for(int n = 0; n < 4; ++n) {
		cout << "##############################" << endl;
		auto sol = subsets(nums);
		for(int i = 0; i < sol.size(); ++i) {
			cout << "[";
			if(!sol[i].empty()) {
				cout << sol[i][0];
			}
			for(int j = 1; j < sol[i].size(); ++j) {
				cout << ", " << sol[i][j];
			}
			cout << "]" << endl;
		}
		nums.push_back(n + 1);
	}
	return 0;
}
