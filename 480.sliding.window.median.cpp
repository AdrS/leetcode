#include <vector>
#include <cstdlib>
#include <set>
#include <iostream>
#include <cassert>

using namespace std;
class Solution {
    double computeMedian(const multiset<int> &A, const multiset<int> &B) {
        assert(abs((int)A.size() - (int)B.size()) <= 1);
        int minA = *A.begin();
        int maxB = *B.rbegin();
        
        // len(A) == len(B) -> averarage min(A) and max(B)
        // len(A) == len(B) + 1 -> min(A)
        // len(A) == len(B) - 1 -> max(B)

        if(A.size() == B.size()) {
            return minA/2.0 + maxB/2.0; // avoid overflow
        } else if(A.size() > B.size()) {
            return minA;
        } else {
            return maxB;
        }
    }
	// If duplicates of val, we only want to remove one of them
	void removeFromSet(multiset<int> &s, int val) {
		auto it = s.find(val);
		s.erase(it);
	}
    void add(multiset<int> &A, multiset<int> &B, int val) {
        int minA = *A.begin();
        int maxB = *B.rbegin();
        if(A.size() < B.size()) {
            if(val >= maxB) {
                A.insert(val);
            } else {
                // have to move element from B to A to keep sizes roughly equal
                B.insert(val);
                A.insert(maxB);
				removeFromSet(B, maxB);
            }
        } else if(A.size() > B.size()){
            if(val <= minA) {
                B.insert(val);
            } else {
                A.insert(val);
                B.insert(minA);
				removeFromSet(A, minA);
            }
        } else {
            if(val >= minA) {
                A.insert(val);
            } else {
                B.insert(val);
            }
        }
        assert(abs((int)A.size() - (int)B.size()) <= 1);
    }
    void remove(multiset<int> &A, multiset<int> &B, int val) {
        int minA = *A.begin();
        int maxB = *B.rbegin();
        if(A.size() < B.size()) {
            if(val <= maxB) {
				removeFromSet(B, val);
            } else {
				removeFromSet(A, val);
                // have to move element from B to A to keep sizes roughly equal
                A.insert(maxB);
				removeFromSet(B, maxB);
            }
        } else if(A.size() > B.size()) {
            if(val >= minA) {
				removeFromSet(A, val);
            } else {
				removeFromSet(B, val);
                // have to move element from A to B to keep sizes roughly equal
                B.insert(minA);
				removeFromSet(A, minA);
            }
        } else {
            if(val <= maxB) {
				removeFromSet(B, val);
            } else {
				removeFromSet(A, val);
            }
        }
        assert(abs((int)A.size() - (int)B.size()) <= 1);
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        if(k == 1) {
            vector<double> medians;
            for(auto n : nums) {
                medians.push_back((double)n);
            }
			return medians;
        }
        // Invariants:
        // A = elts >= than median
        // B = elts <= than median
        // |len(A) - len(B)| <= 1
        multiset<int> A, B;
        if(nums[0] >= nums[1]) {
            A.insert(nums[0]);
            B.insert(nums[1]);
        } else {
            A.insert(nums[1]);
            B.insert(nums[0]);            
        }
        
        for(int i = 2; i < k; ++i) {
            add(A, B, nums[i]);
        }
        vector<double> medians;
        for(int i = k; i < (int)nums.size(); ++i) {
            double median = computeMedian(A, B);
            medians.push_back(median);
            // update sliding window
            add(A, B, nums[i]);
            remove(A, B, nums[i - k]);
			assert(A.size() + B.size() == (unsigned)k);
        }
        medians.push_back(computeMedian(A, B));
        return medians;
    }
};


struct TestCase {
	vector<int> nums;
	int k;
};
int main() {
	TestCase testCases[] = {
		{{1,3,-1,-3,5,3,6,7}, 3},
		{{1,3,-1,-3,5,3,6,7}, 1},
		{{1,3,-1,-3,5,3,6,7}, 2},
		{{1,3,-1,-3,5,3,6,7}, 4},
		{{6,2,7,3,5,2,6,2,7,2,7,4,2,1,6,8,5,3,1,6,8,3,1,5,78,4,2,5,3,6,78,3,5,7,2,9,6,7,8,4,1,3,6,3,5,7,2,9,7,5,3,2,1}, 5},
		{{1,1,1,1,1,1,1,1}, 3}
	};
	Solution s;
	for(auto &testCase : testCases) {
		vector<double> got = s.medianSlidingWindow(testCase.nums, testCase.k);
		for(auto d : got) {
			cout << d << ", ";
		}
		cout << endl;
	}
	return 0;
}
