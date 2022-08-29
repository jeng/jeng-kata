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
        int height(TreeNode* root, int h){
        if (root == nullptr){
            return 0;
        } else if (root->left == nullptr && root->right == nullptr) {
            return h;
        } else {
            return max(height(root->left, h + 1), height(root->right, h + 1));
        }        
    }
        int sumit(TreeNode* root, int h, int m){
        if (root == nullptr){
            return 0;
        } else if (root->left == nullptr && root->right == nullptr){
            if (h == m){
                return root->val;
            }else {
                return 0;
            }
        } else {
            return sumit(root->left, h + 1, m) + sumit(root->right, h + 1, m);
        }
    }
        int deepestLeavesSum(TreeNode* root) {
        int h = height(root, 0);
        return sumit(root, 0, h);                
    }
};