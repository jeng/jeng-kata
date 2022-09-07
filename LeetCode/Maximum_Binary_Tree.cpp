/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void maxTree(TreeNode *node, vector<int>& nums, int start, int end) {
        if (end < start){
            return;
        }
        int m = nums[start];
        int j = start;
        for(int i = start; i <= end; i++){
            if (nums[i] > m) {
                m = nums[i];
                j = i;
            }
        }
        node->val = m;
        if (start < j){
            node->left = new TreeNode();
            maxTree(node->left, nums, start, j-1);
        }
        if (j < end){
            node->right = new TreeNode();
            maxTree(node->right, nums, j+1, end);
        }
    }
    
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode *root = new TreeNode();
        maxTree(root, nums, 0, nums.size() -1);
        return root;
    }
};