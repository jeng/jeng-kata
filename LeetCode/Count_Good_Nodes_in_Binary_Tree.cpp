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
    int count(TreeNode *node, vector<int> path){
        if (node == nullptr){
            return 0;
        } else {
            int val = 1;
            for(int i = 0; i < path.size(); i++){
                if (path[i] > node->val){
                    val = 0;
                }
            }
            vector<int> newpath = path;
            newpath.push_back(node->val);
            return val + count(node->left, newpath) + count(node->right, newpath);
        }
    }
    int goodNodes(TreeNode* root) {
        vector<int> path;
        return count(root, path);
    }
};