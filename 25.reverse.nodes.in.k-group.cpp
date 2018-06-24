#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ostream& operator<<(ostream &os, ListNode* head) {
	while(head) {
		os << head->val;
		head = head->next;
		if(head) {
			os << "->";
		}
	}
	return os;
}

// Reverse a linked list
ListNode *reverse(ListNode* head) {
	ListNode *tail = nullptr;
	while(head) {
		ListNode *next = head->next;
		head->next = tail;
		tail = head;
		head = next;
	}
	return tail;
}

ListNode* reverseKGroup(ListNode* head, int k) {
	if(k < 2 || !head) return head;

	ListNode *rHead = nullptr;
	ListNode *pTail = nullptr;
	ListNode *gHead = head;
	while(gHead) {
		//cout << "gHead: " << gHead << endl;
		//cout << "rHead: " << rHead << endl;

		// Reverse next group of k
		ListNode *gTail = nullptr;
		ListNode *nextpTail = gHead;
		int i = k;
		while(gHead && i) {
			ListNode *next = gHead->next;
			gHead->next = gTail;
			gTail = gHead;
			gHead = next;
			--i;
		}

		// At end of list, not full group
		if(i) {
			gTail = reverse(gTail);
			if(pTail) {
				pTail->next = gTail;
				return rHead;
			} else {
				return gTail;
			}
		}
		//cout << "gHead: " << gHead << endl;
		//cout << "gTail: " << gTail << endl;
		//cout << "rHead: " << rHead << endl;
		//cout << "pTail: " << pTail << endl;
		// Connect to previous groups
		if(pTail) {
			pTail->next = gTail;
		} else {
			// This is the first group
			rHead = gTail;
		}
		pTail = nextpTail;
	}

	return rHead;
}

bool listEq(ListNode *l1, ListNode *l2) {
	if(!l1) return !l2;
	if(!l2) return false;
	if(l1->val != l2->val) return false;
	return listEq(l1->next, l2->next);
}

ListNode* makeList(const vector<int> &nums) {
	ListNode *head = nullptr;
	for(auto it = nums.rbegin(); it != nums.rend(); it++) {
		ListNode *node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

ListNode* copyList(const ListNode *head) {
	if(!head) return nullptr;
	ListNode *c = new ListNode(head->val);
	c->next = copyList(head->next);
	return c;
}

struct TestCase {
	ListNode *list;
	int k;
	ListNode *expected;
};

int main() {
	TestCase testCases[] = {
		{makeList({1,2,3,4,5}), 2, makeList({2,1,4,3,5})},
		{makeList({1,2,3,4,5}), 3, makeList({3,2,1,4,5})},
		{makeList({1,2,3,4,5}), 5, makeList({5,4,3,2,1})},
		{makeList({1,2,3,4,5}), 1, makeList({1,2,3,4,5})},
		{makeList({1,2,3,4,5}), 6, makeList({1,2,3,4,5})},
		{makeList({1,2,3,4,5,6}), 3, makeList({3,2,1,6,5,4})}
	};
	for(auto &tc : testCases) {
		ListNode *list = copyList(tc.list);
		ListNode *got = reverseKGroup(list, tc.k);
		if(!listEq(got, tc.expected)) {
			cerr << "reverseKGroup(" << tc.list << ", " << tc.k << ") got " << got << " expected " << tc.expected << endl;
			
		}
	}
}
