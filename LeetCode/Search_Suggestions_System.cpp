#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct Node {
    map<char, Node*> children;
    //I could walk the trie, one time, once it is built to get the words in order
    //but this also works since the map does an inorder sort.
    map<string, string> words;
};
class Solution {
public:
        void AddWord(Node* trie, string product){
        Node *working = trie;
        for(int i = 0; i < product.size(); i++){
            char c = product[i];            
            if (working->children.find(c) == working->children.end()){
                Node *n = new Node();
                working->children[c] = n;                
                working = n;
            } else {
                working = working->children[c];
            }
                        working->words[product] = "";
        }                    
    }
        Node *BuildTrie(vector<string>& products){
        Node *root = new Node();
        for(auto product : products){
            AddWord(root, product);
        }
        return root;
    }
        vector<string> WordsStartingWith(char c, Node **startLocation){
        vector<string> collection;
        if ((*startLocation)->children.find(c) == (*startLocation)->children.end()){
            return collection;
        }
        *startLocation = (*startLocation)->children[c];
        Node *working = *startLocation;
        for(auto w : working->words){
            if (collection.size() < 3){
                collection.push_back(w.first);
            } else {
                break;
            }
        }
        return collection;
    }
        vector<vector<string>> suggestedProducts(vector<string>& products, string 
        searchWord) {
        vector<vector<string>> result;
        Node *root = BuildTrie(products);
        Node *start = root;
        bool done = false;
        for(auto c : searchWord){
            vector<string> collection = WordsStartingWith(c, &start);
            if (collection.size() == 0)
                done = true;
            if (done){
                vector<string> v;
                result.push_back(v);
            } else {
                result.push_back(collection);
            }
        }
        return result;
    }
};