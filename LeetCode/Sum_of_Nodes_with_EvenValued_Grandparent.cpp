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
struct TreeMeta {
    TreeNode *node;
    int parentVal;
    int grandparentVal;    
};
class Solution {
public:    
        int sumEvenGrandparent(TreeNode* root) {
        queue<TreeMeta> q;
        int sum = 0;
                TreeMeta tm;
        tm.node = root;
        tm.parentVal = 0;
        tm.grandparentVal = 0;
        q.push(tm);
                while(q.size() > 0){
            TreeMeta n = q.front();
            q.pop();
                        if (n.grandparentVal != 0 && n.grandparentVal % 2 == 0) {
                sum += n.node->val;
            }
                        /*
            cout << " val " << n.node->val 
                 << " parent " << n.parentVal << " gpv " << n.grandparentVal
                << "sum " << sum << endl;
            */
                        if (n.node->left != nullptr){
                TreeMeta tm;
                tm.node = n.node->left;
                tm.parentVal = n.node->val;
                tm.grandparentVal = n.parentVal;                
                q.push(tm);
            }
            if (n.node->right != nullptr){
                TreeMeta tm;
                tm.node = n.node->right;
                tm.parentVal = n.node->val;
                tm.grandparentVal = n.parentVal;
                q.push(tm);
            }            
        }
        return sum;
    }
};