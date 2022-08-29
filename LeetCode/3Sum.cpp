class Solution {
public:
    void
    Sort3(vector<int> &v3){
        if (v3[1] < v3[0]){
            swap(v3[0], v3[1]);
        }
        if (v3[2] < v3[0]){
            swap(v3[0], v3[2]);
        }
        if (v3[2] < v3[1]){
            swap(v3[1], v3[2]);
        }
    }
    vector<vector<int>> threeSum(vector<int> &input){
        unordered_set <string> history;
        vector<vector<int>> results;
        int idx = 0;
        if (input.size() <= 0){        
            return results;
        }
        sort(input.begin(), input.end());
        for(int i = 0; i < input.size(); i++){    
            int last_j = INT_MAX;
            for(int j = i + 1; j < input.size(); j++){                        
                if (last_j == input[j])
                    continue;
                int n  = input[i] + input[j];
                int m = n * -1;
                bool found = binary_search(input.begin(), input.end(), m);
                if (found){                                                    
                    vector<int> found(3);
                    auto lower = lower_bound(input.begin(), input.end(), m);
                    auto upper = upper_bound(input.begin(), input.end(), m);
                    int size = upper - lower;
                    found[0] = input[i];
                    found[1] = input[j];
                    found[2] = m;
                    for(int i = 0; i < 3; i++){
                        if (found[i] == m)
                            size--;
                    }
                    if (size >= 0){
                        Sort3(found);
                        string s = to_string(found[0]) + "_" + to_string(found[1]) + 
                            "_" + to_string(found[2]);
                        if (history.find(s) == history.end()){
                            history.insert(s);
                            results.push_back(found);
                        }                    
                    }
                }
                last_j = input[j];
            }
        }
        return results;
    }
};