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
    TreeNode* createBinaryTree(vector<vector<int>>& matrix) {
        unordered_map<int, bool> hasParent;
        unordered_map<int, vector<int>> children;
        for(int i = 0; i < matrix.size(); i++){
            int parent = matrix[i][0];
            int child = matrix[i][1];
            bool isLeft = (matrix[i][2] == true);
            if (hasParent.find(parent) == hasParent.end()){
                hasParent[parent] = false;
            }
            if (children.find(parent) == children.end()){
                vector<int> c(2);
                children[parent] = c;
            }
            if (isLeft){
                children[parent][0] = child;
            } else {
                children[parent][1] = child;
            }
            hasParent[child] = true;
        }
                              int root = 0;
        for(auto e : hasParent){
            if (!e.second){
                root = e.first;
            }
        }
                              queue<TreeNode *> q;
        TreeNode *head = new TreeNode(root);
        q.push(head);
        while(!q.empty()){
            TreeNode *worker = q.front();
            q.pop();            
                        if (children.find(worker->val) == children.end())
                continue;
                        vector<int> c = children[worker->val];
            if (c[0] > 0){                
                worker->left = new TreeNode(c[0]);                
                q.push(worker->left);
            }
            if (c[1] > 0){
                worker->right = new TreeNode(c[1]); 
                q.push(worker->right);
            }
        }
        return head;
    }
};