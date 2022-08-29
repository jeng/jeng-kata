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
    int BuildGreaterSumTree(TreeNode* root, int parentVal){        
        if (root == nullptr){
            return parentVal;
        }        
        root->val += BuildGreaterSumTree(root->right, parentVal);
        int left = BuildGreaterSumTree(root->left, root->val);
        return left;
    }
        TreeNode* bstToGst(TreeNode* root) {
        BuildGreaterSumTree(root, 0);
        return root;        
    }
};