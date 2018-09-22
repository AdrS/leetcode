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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> traversal;
        vector<int> level;
        
        queue<TreeNode *> pending;
        pending.push(root);
        // use nullptr as sentinal to mark end of level
        pending.push(nullptr);
        while(!pending.empty()) {
            TreeNode *cur = pending.front();
            pending.pop();
            if(cur) {
                level.push_back(cur->val);
                if(cur->left) {
                    pending.push(cur->left);
                }
                if(cur->right) {
                    pending.push(cur->right);
                }   
            } else {
                // empty level -> end of tree
                if(level.empty()) break;
                traversal.push_back(level);
                level.clear();
                pending.push(nullptr);
            }
        }
        return traversal;
    }
};
