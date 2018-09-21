#include <cassert>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Access {
	int key;
	Access *next;
	Access *prev;
	Access(int key, Access *next, Access *prev) : key(key), next(next), prev(prev) {}
};

class LRUCache {
	Access *lru, *mru;
	int capacity;
	unordered_map<int, pair<int, Access*>> table;

	// Takes pointer to order elt in cache and updates
	// it to be MRU
	void access(Access *elt) {
		// element is already mru
		if(elt == mru) return;

		// Remove element from where it was in the access order
		if(elt->prev) {
			elt->prev->next = elt->next;
		} else {
			// element being accessed was LRU -> must update lru
			lru = lru->next;
		}
		// elt != mru => elt->next != nullptr
		elt->next->prev = elt->prev;

		// Make element the new MRU
		mru->next = elt;
		elt->prev = mru;
		elt->next = nullptr;
		mru = elt;
	}

public:
	void print() {
		cout << "##############################" << endl;
		cout << "capacity: " << capacity << endl;
		for(auto &i : table) {
			cout << i.first << " -> " << i.second.first << endl;
		}
		cout << "MRU to LRU: ";
		Access *cur = mru;
		while(cur) {
			cout << cur->key << "(" << cur->next  << " " << cur << " " << cur->prev << ") , ";
			cur = cur->prev;
		}
		cout << "LRU: " << lru << " MRU: " << mru << endl;
	}

	LRUCache(int capacity) : lru(nullptr), mru(nullptr), capacity(capacity) {
		print();
	}
	int get(int key) {
		cout << "get(" << key << ")" << endl;
		auto it = table.find(key);
		// Item not found
		if(it == table.end()) {
			return -1;
		}
		// Update access order information
		access(it->second.second);
		print();
		// Return value
		return it->second.first;
	}
	
	void put(int key, int value) {
		cout << "put(" << key << "-> " << value << ")" << endl;
		// First time cache is accessed
		if(!mru) {
			mru = lru = new Access(key, nullptr, nullptr);
		} else {
			if(capacity == 1) {
				table.clear();
				table[key] = pair<int, Access*>(value, mru);
				return;
			}
			auto it = table.find(key);
			// New element
			if(it == table.end()) {
				// If table is full, evict LRU
				if(table.size() == capacity) {
					cout << "Evict " << lru->key << endl;
					table.erase(table.find(lru->key));
					assert(capacity > 1);
					lru->next->prev = nullptr;
					lru = lru->next;
					print();
				}
				mru = new Access(key, nullptr, mru);
				mru->prev->next = mru;
			// Update
			} else {
				it->second.first = value;
				access(it->second.second);
			}
		}
		table[key] = pair<int, Access*>(value, mru);
		print();
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

void test1() {
	LRUCache cache(5 /* capacity */ );
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 5; ++j) {
			cache.put(j,j);
		}
	}
}

void test2() {
	LRUCache cache(2);
	cache.put(2, 1);
	cache.put(2, 2);
	assert(cache.get(2) == 2);
	cache.put(1, 1);
	cache.put(4, 1);
	assert(cache.get(2) == -1);
}

int main() {
	test1();
	test2();
	LRUCache cache( 2 /* capacity */ );

	cache.put(1, 1);
	cache.put(2, 2);
	assert(cache.get(1) == 1);	   // returns 1
	cache.put(3, 3);	// evicts key 2
	assert(cache.get(2) == -1);	   // returns -1 (not found)
	cache.put(4, 4);	// evicts key 1
	assert(cache.get(1) == -1);	   // returns -1 (not found)
	assert(cache.get(3) == 3);	   // returns 3
	assert(cache.get(4) == 4);	   // returns 4
	return 0;
}
