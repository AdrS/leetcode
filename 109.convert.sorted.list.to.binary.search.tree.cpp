/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    /*
    h = 1 => 1 node
    h = 2 => 2 - 3 nodes
    h = 3 => 4 - 7 nodes
    h = 4 => 7 - 15
    h = 5 => 12 - 31
    
    Balanced height h tree has between  and 2^h - 1 nodes (inclusive)

Claim: for balanced tree |left subtree| = |right subtree| +/- 1 for all nodes
    Proof:
    case leaf => |left subtree| = 0 = |right subtree|
    Suppose claim holds for all trees with < n nodes
    false
    */
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        if(!head->next) return new TreeNode(head->val);
        ListNode *left = head;
        ListNode *right = head;
        ListNode *mid = head;
        ListNode *prev;
        while(right->next) {
            prev = mid;
            mid = mid->next;
            right = right->next;
            if(!right->next) {
                break;
            }
            right = right->next;
        }
        prev->next = nullptr;
        TreeNode *tree = new TreeNode(mid->val);
        tree->left = sortedListToBST(left);
        tree->right = sortedListToBST(mid->next);
        return tree;
    }
};
// O(n) fastest
