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
struct SubCount {
    int sub;
    int count;
};
class Solution {    
public:
        SubCount sumCountSub(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};  
        } else {
            SubCount left = sumCountSub(root->left);
            SubCount right = sumCountSub(root->right);
            return {left.sub + right.sub + root->val, left.count + right.count + 1};
        }
    }
        int countthem(TreeNode *root){
        if (root == nullptr) {
            return 0;        
        } else {            
            SubCount left = sumCountSub(root->left);
            SubCount right = sumCountSub(root->right);
            int val = left.sub + right.sub + root->val;
            int count = left.count + right.count + 1;
            int avg = val/count;
                                    int result = 0;
            if (avg == root->val) {
                result = 1;
            }
                        return result + countthem(root->left) + countthem(root->right);
        }
    }
        int averageOfSubtree(TreeNode* root) {
        return countthem(root);        
    }
};