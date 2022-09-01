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
struct token {
    int value;
    int depth;
};

class Solution {
public:
    bool isNumber(char c) {
        return ('0' <= c && c <= '9');
    }
    
    token getToken(string traversal, int &idx) {
        int state = 0;
        token tok;
        tok.value = 0;
        tok.depth = 0;
        while(idx < traversal.size() && state != 2){

            if (isNumber(traversal[idx])){
                tok.value = tok.value * 10;
                tok.value = tok.value + (traversal[idx] - '0');
                state = 1;
            }
            if (traversal[idx] == '-'){
                if(state == 0)
                    tok.depth++;
                else
                    state = 2;
            }
            
            idx++;
        }
        return tok;
    }
    
    TreeNode* recoverFromPreorder(string traversal) {
        int idx = 0;
        bool firstPass = true;
        TreeNode* result;
        vector<vector<TreeNode*>> history;
        
        while(idx < traversal.size()){
            if (!firstPass)
                idx--;
            
            token tok = getToken(traversal, idx);
            
            if (firstPass){
                result = new TreeNode(tok.value);
                vector<TreeNode*> row;
                history.push_back(row);
                history[0].push_back(result);
                firstPass = false;
            } else {
                int size = history[tok.depth-1].size();
                TreeNode* tree = history[tok.depth-1][size-1];
                TreeNode* newNode = new TreeNode(tok.value);
                if (tree->left == nullptr){
                    tree->left = newNode;
                }else {
                    tree->right = newNode;
                }
                if (tok.depth >= history.size()){
                    vector<TreeNode*> row;
                    history.push_back(row);
                }
                history[tok.depth].push_back(newNode);
            }
            
        }
        return result;
    }
};