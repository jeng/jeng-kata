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
    int getParent(int n){
        int row = floor(log2(n));
        int start = pow(2, row);
        int parentOffset = (n - start) / 2;
        int parentStart = pow(2, row-1);
        return parentStart + parentOffset;
    }
    int getChild(int n){
        int row = floor(log2(n));
        return pow(2, row+1) + 2 * (n - pow(2, row));
    }
    TreeNode* toFullTree(vector<int> entry){
        TreeNode* result = new TreeNode();
        unordered_map<int, TreeNode*> history;
        history[1] = result;
        for(int i = 0; i < entry.size(); i++){
            int x = entry[i];
            int leftChild = getChild(x);
            int rightChild = leftChild + 1;
            TreeNode* leftNode = new TreeNode();
            TreeNode* rightNode = new TreeNode();
            //new node left
            history[entry[i]]->left = leftNode;
            history[entry[i]]->right = rightNode;
            history[leftChild] = leftNode;
            history[rightChild] = rightNode;
        }
        return result;
    }
        vector<TreeNode*> permuteTrees(int numberOfNodes, int nodeLimit){
        unordered_map<int, vector<vector<int>>> history;
        vector<TreeNode*> result;
        vector<int> init{1};
        vector<vector<int>> hinit{init};
        history[1] = hinit;
        if (nodeLimit == 1)
            result.push_back(new TreeNode());                
        else if (nodeLimit == 3)
            result.push_back(toFullTree(init));
        for(int i = 2; i < numberOfNodes; i++){
            int parent = getParent(i);
            vector<vector<int>> parentList = history[parent];
            for(int j = 0; j < parentList.size(); j++){
                vector<int> copy = parentList[j];
                copy.push_back(i);
                                int nodeCount = 1 + (2 * copy.size());
                if ( nodeCount > nodeLimit)
                    continue;
                else if (nodeCount == nodeLimit)                                
                    result.push_back(toFullTree(copy));
                                //update the cache
                for(int m = 0; m < copy.size(); m++){
                    if (history.find(copy[m]) == history.end()){
                        vector<vector<int>> v;
                        history[copy[m]] = v;
                    }
                    history[copy[m]].push_back(copy);
                }
            }
        }
        return result;
    }
        vector<TreeNode*> allPossibleFBT(int n) {
        int possible = pow(2, floor(n/2));
        return permuteTrees(possible, n);
    }
};