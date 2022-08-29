/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right
     (right) {}
 * };
 */
class Solution {
public:
    int visited = INT_MAX;
        TreeNode *getNext(stack<TreeNode*> &s, TreeNode *node){        
        if (node == nullptr)
            return node;
        if (node->val == visited){
            if (node->right != nullptr && node->right->val != visited){
                node = node->right;                
            } else {
                if (s.empty()){
                    return nullptr;
                }                
                node = s.top();
                s.pop();                
                return node;                
            }
        }        
        while(node != nullptr){
            s.push(node);
            node = node->left;
        }
        node = s.top();
        s.pop();        
        return node;
    }
        vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> result;
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        TreeNode *n1 = getNext(s1, root1);
        TreeNode *n2 = getNext(s2, root2);
                        while(true){
            if (n1 == nullptr && n2 == nullptr){
                return result;
            } else if (n1 == nullptr){
                result.push_back(n2->val);
                n2->val = visited;
                n2 = getNext(s2, n2);                
            } else if (n2 == nullptr){
                result.push_back(n1->val);
                n1->val = visited;
                n1 = getNext(s1, n1);                                
            } else if (n1->val <= n2->val){
                result.push_back(n1->val);
                n1->val = visited;
                n1 = getNext(s1, n1);
            } else {
                result.push_back(n2->val);
                n2->val = visited;
                n2 = getNext(s2, n2);
            }            
        }         
    }
};