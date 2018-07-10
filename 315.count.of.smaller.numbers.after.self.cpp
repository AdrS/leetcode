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

// Number of smaller values
// is sum of the number of elts in the left branches
// not taken while traversing tree
struct Node {
	int val;
	int numLeft;
	int numEq;
	Node *left;
	Node *right;
	Node(int val) : val(val), numLeft(0), numEq(1), left(nullptr), right(nullptr) {}
};

void printTree(Node *root) {
	cout << '(';
	if(root) {
		printTree(root->left);
		cout << " " << root->val << "[" << root->numEq << "] > " << root->numLeft << " ";
		printTree(root->right);
	} 
	cout << ')';
}

vector<int> countSmaller(vector<int>& nums) {
	if(nums.empty()) {
		return vector<int>();
	}

	vector<int> counts(nums.size());

	// binary tree
	Node *root = new Node(nums.back());
	for(int i = (int)nums.size() - 2; i >= 0; --i) {
		/*
		cout << "Round " << i;
		printTree(root);
		cout << endl;
		*/
		Node *prev = root;
		Node *cur = root;
		int numSmaller = 0;
		while(cur) {
			if(cur->val < nums[i]) {
				numSmaller += (cur->numLeft + cur->numEq);
				prev = cur;
				cur = cur->right;
			} else if(cur->val > nums[i]) {
				cur->numLeft++;
				prev = cur;
				cur = cur->left;
			} else {
				cur->numEq++;
				numSmaller += cur->numLeft;
				break;
			}
		}
		if(!cur) {
			if(prev->val < nums[i]) {
				prev->right = new Node(nums[i]);
			} else {
				prev->left = new Node(nums[i]);
			}
		}
		counts[i] = numSmaller;
	}
	/*
	cout << "Round 0";
	printTree(root);
	cout << endl << endl; */
	return counts;
}

int main() {
	vector<vector<int>> tests = {
		{5,2,6,1},
		{5,2,2, 6,5, 1},
		{},
		{5,4,3,2,1},
		{1,2,3,4,5,6},
		{4, 5, 5, 6, 3, 0, 3, 2, 6, 9, 1, 9, 1, 7, 10},
		{0, 25, 4, 17, 3, 1, 20, 13, 8, 5, 7, 14, 20, 6, 19}
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

