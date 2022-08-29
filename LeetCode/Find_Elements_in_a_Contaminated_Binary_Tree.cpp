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
class FindElements {
public:
    TreeNode *local;
    FindElements(TreeNode* root) {
        local = root;
        root->val = 0;
        int x = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(q.size() > 0){
            TreeNode* t = q.front();
            q.pop();
            if (t->left != nullptr){
                t->left->val = 2 * t->val + 1;
                q.push(t->left);
            }
            if (t->right != nullptr){
                t->right->val = 2 * t->val + 2;
                q.push(t->right);
            }
        }        
    }
        bool find(int target) {
        queue<TreeNode*> q;
        q.push(local);
        while(q.size() > 0){
            TreeNode *t = q.front();
            q.pop();
            if (t->val == target){
                return true;
            }
            if (t->val > target){
                return false;
            }
            if (t->left != nullptr){
                q.push(t->left);
            }
            if (t->right != nullptr){                
                q.push(t->right);
            }
        }
        return false;        
    }
};
/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */