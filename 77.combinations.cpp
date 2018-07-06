#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// backtracking solution
void aux(vector<vector<int>> &solutions, vector<int> &cur, int min, int max, int left) {
	if(left) {
		int numsToChooseFrom = max - min + 1;

		// combinations with min
		if(numsToChooseFrom > 0) {
			cur.push_back(min);
			aux(solutions, cur, min + 1, max, left - 1);
			cur.pop_back();
		}
		// combinations without min
		if(numsToChooseFrom > left) {
			aux(solutions, cur, min + 1, max, left);
		}
	} else {
		solutions.push_back(cur);
	}
}

vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> combinations;
	vector<int> cur;
	aux(combinations, cur, 1, n, k);
	return combinations;
}

int main() {
	for(int n = 0; n < 4; ++n) {
		cout << "##############################" << endl;
		for(int k = 0; k <= n; ++k) {
			cout << "Combinations of " << k << " numbers out of 1 ... " << n << endl;
			auto sol = combine(n, k);
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
		}
	}
	return 0;
}
