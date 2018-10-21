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
    /*bool contains(TreeNode *root, int v) {
        while(root) {
            if(root->val < v) root = root->right;
            else if(root->val > v) root = root->left;
            else return true;
        }
        return false;    
    }*/
    void inorderTraversal(vector<int> &items, TreeNode *root) {
        if(!root) return;
        if(root->left) {
            inorderTraversal(items, root->left);
        }
        items.push_back(root->val);
        if(root->right) {
            inorderTraversal(items, root->right);
        }
    }
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> items;
        inorderTraversal(items, root);
        int i = 0;
        int j = (int)items.size() - 1;
        while(i < j) {
            int s = items[i] + items[j];
            if(s < k) {
                ++i;
            } else if(s > k) {
                --j;
            } else {
                return true;
            }
        }
        return false;
        /*
        if(!root) return false;
        int c = k - root->val;
        if(c <= root->val && contains(root->left, c)) return true;
        if(c >= root->val && contains(root->right, c)) return true;
        return findTarget(root->left, k) || findTarget(root->right, k); */
    }
};
