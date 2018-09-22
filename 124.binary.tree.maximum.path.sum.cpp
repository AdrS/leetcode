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
    // Returns max path in tree and max path ending at root
    void opt(TreeNode *root, int &max_path, int &max_end_root) {
        int lmax, lrmax, rmax, rrmax;
        // path with only root
        max_end_root = max_path = root->val;
        // max path including root
        int max_path_root = root->val;
        if(root->left) {
            opt(root->left, lmax, lrmax);
            if(lrmax > 0) {
                max_path_root = max_end_root = lrmax + root->val;
            }
            max_path = max(max_path, lmax);
        }
        if(root->right) {
            opt(root->right, rmax, rrmax);
            if(rrmax > 0) {
                max_end_root = max(max_end_root, rrmax + root->val);
                max_path_root += rrmax;
            }
            max_path = max(max_path, rmax);
        }
        max_path = max(max(max_path, max_path_root), max_end_root);
    }
public:
    int maxPathSum(TreeNode* root) {
        int max_path, max_path_root;
        opt(root, max_path, max_path_root);
        return max_path;
    }
};
