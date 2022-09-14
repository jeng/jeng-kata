class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> history(m);
        vector<int> result;
        for(int i = 0; i < m; i++){
            history[i] = i;
        }
        for(int i = 0; i < queries.size(); i++){
            int q = queries[i] - 1;
            int x = history[q];
            result.push_back(x);
            history[q] = 0;
            for(int j = 0; j < history.size(); j++){
                if (history[j] < x && j != q) {
                    history[j]++;
                }
            }
        }
        return result;
    }
};