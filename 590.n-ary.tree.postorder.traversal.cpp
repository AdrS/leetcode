/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*//*
class Solution {
    void traverse(Node *root, vector<int> &results) {
        if(!root) return;
        for(auto c : root->children) {
            traverse(c, results);
        }
        results.push_back(root->val);
    }
public:
    vector<int> postorder(Node* root) {
        vector<int> results;
        traverse(root, results);
        return results;
    }
};
// 80 ms
*/
class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<pair<Node*, int>> s;
        vector<int> results;
        s.push(pair<Node*, int>(root, 0));
        while(!s.empty()) {
            auto cur = s.top();
            s.pop();
            Node *node = cur.first;
            if(!node) continue;
            // If we have processed node's children, then process node
            if(node->children.size() == cur.second) {
                results.push_back(node->val);
            } else {
                s.push(pair<Node*, int>(node, cur.second + 1));
                s.push(pair<Node*, int>(node->children[cur.second], 0));
            }
        }
        return results;
    }
};
// 48 ms

/* 32 ms
public:
    
    vector<int> postorder(Node* root) {
        vector<int> res;
        int n;
        stack<Node*> poTrav_stk;         
        if (root){
            poTrav_stk.push(root);
            while(!poTrav_stk.empty()){                
                root=poTrav_stk.top();
                if(!root){
                    poTrav_stk.pop();
                    res.push_back((poTrav_stk.top())->val);
                    poTrav_stk.pop();
                }
                else{
                    poTrav_stk.push(NULL);
                    n=root->children.size();
                    for(int i=n-1;i>=0;i--)
                        poTrav_stk.push(root->children[i]);
                }
            }        
        }
        return(res);
    }
}; */
