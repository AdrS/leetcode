#include <vector>
#include <cassert>

using namespace std;

// zero based indexing
int parent(int idx) { return (idx + 1)/2 - 1; }
int leftChild(int idx) { return 2*(idx + 1) - 1; }
int rightChild(int idx) { return 2*(idx + 1); }

class Heap {
	vector<int> elts;
	void heapify_up(int idx);
	void heapify_down(int idx);
	bool isLeaf(int idx) { return (unsigned)idx >= elts.size()/2; }
public:
	int size() const { return elts.size(); }
	bool empty() const { return elts.empty(); }
	void push(int e);
	int top() const {
		assert(!empty());
		return elts[0];
	}
	void pop();
};

// When element elts[idx] changes, makes shifts
// necessary to restore invariants
void Heap::heapify_up(int idx) {
	// If greater than parent, swap with parent
	while(idx != 0 && elts[idx] > elts[parent(idx)]) {
		swap(elts[idx], elts[parent(idx)]);
		idx = parent(idx);
	}
}

void Heap::heapify_down(int idx) {
	// If less that a child, swap with largest child
	do {
		int largest = idx;
		int lc = leftChild(idx);
		int rc = rightChild(idx);
		if(lc < size() && elts[largest] < elts[lc]) {
			largest = lc;
		}
		if(rc < size() && elts[largest] < elts[rc]) {
			largest = rc;
		}
		if(largest == idx) break;
		swap(elts[idx], elts[largest]);
		idx = largest;
	} while(true);
}

void Heap::push(int e) {
	elts.push_back(e);
	heapify_up(elts.size() - 1);
}

void Heap::pop() {
	assert(!empty());
	elts[0] = elts.back();
	elts.pop_back();
	heapify_down(0);
}

int main() {
	Heap h;
	for(int max = 0, g = 3; g != 1; g = ((g * 3) % 17)) {
		if(g > max) {
			max = g;
		}
		h.push(g);
		assert(h.top() == max);
	}
	for(int i = 16; i > 1; --i) {
		assert(h.size() == i - 1);
		assert(h.top() == i);
		h.pop();
	}
	assert(h.empty());
	return 0;
}
