/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // Linear time complexity. Context space besides input.
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        // Find the midpoint and end of the linked-list
        ListNode* midpoint = head;
        ListNode* end = head;
        // The idea is `end` advances twice as fast as `midpoint`
        // so when it reaches the end, `midpoint` will be at the midpoint.
        while(end->next && end->next->next) { // While not at end
            midpoint = midpoint->next;
            end = end->next->next;
        }
        ListNode *right = reverse(midpoint->next);
        midpoint->next = nullptr;
        ListNode *left = head->next;
        // Merge the left have and the reversed right half of the list
        while (left && right) {
            head = head->next = right;
            right = right->next;
            head = head->next = left;
            left = left->next;
        }
        if (left) {
            head = head->next = left;
        } else if (right) {
            head = head->next = right;
        }
        head->next = nullptr;
    }

    // Linear time and space complexity
    void reorderList1(ListNode* head) {
        // Everything except for head
        std::vector<ListNode*> nodes;
        for (ListNode* i = head->next; i; i = i->next) {
            nodes.push_back(i);
        }
        int left_i = 0;
        int right_i = nodes.size() - 1;
        while (left_i < right_i) {
            // Alternate between adding the righmost and leftmost remaining nodes
            head = head->next = nodes[right_i--];
            head = head->next = nodes[left_i++];            
        }
        if (left_i == right_i) {
            head = head->next = nodes[left_i];
        }
        head->next = nullptr;
    }

    // Constant additional space besides input. Quadratic time complexity.
    void reorderList2(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        while(head->next) {
            head = head->next = reverse(head->next);
        }
    }

    ListNode* reverse(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while(cur) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
