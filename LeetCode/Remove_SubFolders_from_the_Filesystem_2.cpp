class Solution {
        //We will need to split the directories by the path
    //It doesn't say if they're defined in order
    //for example do we always get ["/a", "/a/b"] or can we get ["/a/b", "/a"]
    //In the second case we would want to sort by the path length
    //
    //This would be really important if we get something of the form
    //["/c/d", "/c/d/e", "/c"]
    //since in this order we would consider "/c/d" to be a complete folder
    //
    //What would the tree ["/a", "/a/b", "/c/d", "c/d/e", "/c/f"] look like
    //
    //                        root
    //                   /     |    \
    //                 a     c/d    c/f
    //               /      /
    //             b       e 
    //
    // Directory names can have a slash so if we don't find a parent we would need to 
        collapse the name
    // or we could just walk the path at the root
    //
    // What does this look like if we treate it as a string search and replace?
    //   Well "/a"  is a prefix of "/a/b" so we remove /b
    //   but "/cheese" is a prefix of "/cheeseburger" and we don't remove that
    //   if we append an ending "/" then we could use it
    //
    // for i in list add a slash to the end if it doesn't have one O(n)
    // sort the list O(nlogn)
    // for i in list if prefix: O(n)
    //    binary search to prefix O(logn)
    //    remove item O(1) // hopefully
        public:
            vector<string> removeSubfolders(vector<string>& folder) {
        for (int i = 0; i < folder.size(); i++){
            if (folder[i][folder[i].size()] != '/'){
                folder[i] += '/';
            }
        }
                    sort(folder.begin(), folder.end());
        unordered_map<int, int> history;
                vector<string> result;
        for(int i = 0; i < folder.size(); i++){
            //cout << "i " << folder[i] << endl;
            if (history.find(i) == history.end()){
                auto low = lower_bound(folder.begin(), folder.end(), folder[i]);
                int start = low - folder.begin();
                for(int j = start; j < folder.size(); j++){
                    //cout << "j " << folder[j] << endl;
                    if (folder[j].rfind(folder[i], 0) == 0){
                        //cout << "found " << folder[j] << " " << folder[i] << endl;
                        history[j] = j;
                    } else {
                        break;
                    }                        
                }
                folder[i].pop_back();
                result.push_back(folder[i]);
            } else {
                //cout << "weird" << endl;
            }
        }
        return result;
    }
};