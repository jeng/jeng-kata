struct element_t {
    int before;
    int after;
};
class Solution {
public:
    int countSubstrings(string s, string t) {
        vector<vector<element_t>> history;
        int count = 0;
        for(int i = 0; i < s.size(); i++){
            vector<element_t> row;
            history.push_back(row);
            for(int j = 0; j < t.size(); j++){
                element_t e;
                history[i].push_back(e);
                if (s[i] == t[j]){
                    if (0 <= i-1 && 0 <= j-1){
                        count += history[i-1][j-1].before;
                        history[i][j].before = history[i-1][j-1].before;
                        history[i][j].after = history[i-1][j-1].after + 1;
                    } else {
                        history[i][j].before = 0;
                        history[i][j].after = 1;
                    }
                } else {
                    if (0 <= i-1 && 0 <= j-1){
                        history[i][j].before = history[i-1][j-1].after + 1;
                        history[i][j].after = 0;
                        count += history[i][j].before;
                    } else {
                        history[i][j].before = 1;
                        history[i][j].after = 0;
                        count += 1;
                    }
                }
            }
        }
        return count;   
    }
};