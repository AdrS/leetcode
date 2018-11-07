/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> levels;
        if(!root) return levels;

        queue<Node*> pending;
        pending.push(root);
        vector<int> level;
        int leftOnLevel = 1;
        int onNextLevel = 0;
        while(!pending.empty()) {
            Node *cur = pending.front();
            pending.pop();
            for(Node *child : cur->children) {
                if(child) {
                    pending.push(child);
                    ++onNextLevel;
                }
            }
            level.push_back(cur->val);
            --leftOnLevel;
            if(!leftOnLevel) {
                levels.push_back(level);
                level = {};
                leftOnLevel = onNextLevel;
                onNextLevel = 0;
            }
        }
        return levels;
    }
};
