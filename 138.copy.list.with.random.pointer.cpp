#include <iostream>
#include <unordered_map>

using namespace std;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

RandomListNode *copyRandomList(RandomListNode *head) {
	// Mapping between ptr in old list and analogous ptr in new list
	unordered_map<RandomListNode*, RandomListNode*> translation;

	// Make shallow copy
	RandomListNode *cur = head;
	RandomListNode beforeCopy(0);
	RandomListNode *copyPos = &beforeCopy;
	while(cur) {

		RandomListNode *nodeCopy = new RandomListNode(cur->label);
		nodeCopy->random = cur->random;

		translation[cur] = nodeCopy;
		copyPos->next = nodeCopy;
		copyPos = nodeCopy;

		cur = cur->next;
	}
	// Fix random pointers using translation table
	cur = beforeCopy.next;
	while(cur) {
		cur->random = translation[cur->random];
		cur = cur->next;
	}
	return beforeCopy.next;
}

void print(RandomListNode *head) {
	if(head) {
		cout << (void*)head << ": " << head->label << " -> " << (void*)head->next << " -? " << (void*)head->random << endl;
		print(head->next);
	}
}

int main() {
	RandomListNode nodes[] = {1,2,3,4,5,6,7};
	nodes[0].next = &nodes[1];
	nodes[0].random = &nodes[3];
	nodes[1].next = &nodes[2];
	nodes[1].random = &nodes[1];
	nodes[2].next = &nodes[3];
	nodes[2].random = &nodes[6];
	nodes[3].next = &nodes[4];
	nodes[3].random = &nodes[3];
	nodes[4].next = &nodes[5];
	nodes[4].random = &nodes[3];
	nodes[5].next = &nodes[6];
	nodes[5].random = &nodes[2];
	nodes[6].next = nullptr;
	nodes[6].random = nullptr;
	print(nodes);

	RandomListNode *copy = copyRandomList(nodes);
	print(copy);
	return 0;
}
