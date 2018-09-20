#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

void showMap(const unordered_map<int, int> &m) {
	cout << "Seq list: " << endl;
	for(auto &i : m) {
		cout << i.first << "-> " << i.second << endl;
	}
}

class Solution {
public:
    int longestConsecutive(const vector<int>& nums) {
		cout << "Staring..." << endl;
		cout << "##################################################" << endl;
        // map integer to length of sequence starting or ending at it
        // negative => staring
        unordered_map<int, int> seqLen;
        int maxLen = 0;
        for(int num : nums) {
			cout << "num: " << num << endl;
            // only process number once
            auto it = seqLen.find(num);
            if(it != seqLen.end()) {
				cout << "skipping ..." << it->first << " " << it->second << endl;;
				continue;
			}

            auto left = seqLen.find(num - 1);
            auto right = seqLen.find(num + 1);
            int len = 1;
            
			showMap(seqLen);
            // see if num connects two seperate sequences
            if(left != seqLen.end() && right != seqLen.end()) {
				cout << " connect ..";
                // left must be end of something
                assert(left->second > 0);
                // right must be beginning of something
                assert(right->second <= 1);
                len = left->second + 1 + abs(right->second);
                seqLen[num - left->second] = -len;
                seqLen[num + abs(right->second)] = len;
				// mark number as present
				seqLen[num] = 0;
            // sequence extends end of another
            } else if(left != seqLen.end()) {
				cout << "extend end ..";
                len = abs(left->second) + 1;
                seqLen[num - len + 1] = -len;
                seqLen[num] = len;
            // sequence extrends beginning of another
            } else if(right != seqLen.end()) {
				cout << "extend start ..";
                len = abs(right->second) + 1;
                seqLen[num + len - 1] = len;
                seqLen[num] = -len;
            } else {
				cout << "new seq";
                seqLen[num] = 1;
            }
			showMap(seqLen);
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }
};

int main() {
	Solution s;
	assert(s.longestConsecutive({100,4,200,1,3,2}) == 4);
	assert(s.longestConsecutive({1,1,2,3,1,3,4}) == 4);
	assert(s.longestConsecutive({3,2,5,1,6,2,6,3,78,3,1,6,3,46,4}) == 6);
	assert(s.longestConsecutive({4,0,-4,-2,2,5,2,0,-8,-8,-8,-8,-1,7,4,5,5,-4,6,6,-3}) == 5);
	assert(s.longestConsecutive({0,3,7,2,5,8,4,6,0,1}) == 9);
}
