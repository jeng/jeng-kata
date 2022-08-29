class Solution {
public:
    int maxPart(vector<int> &a, int i, int j){
        int result = 0;
        for(; i <= j; i++){
            result = max(result, a[i]);
        }
        return result;
    }
    int maxSumAfterPartitioning(vector<int>& a, int k) {
        vector<int> history(a.size());
        history[0] = a[0];
        for(int i = 1; i < a.size(); i++){
            int n = 0;
            for(int j = 1; j <= k; j++){
                int offset = i-j;
                int value = 0;
                if (offset >= 0){
                    value = history[offset];
                }
                if ((j-1) >= 0 && (i-(j-1)) >= 0)
                    n = max(n, value + (j * maxPart(a, i-(j-1), i)));
            }
            history[i] = n;
        }
        return history[a.size()-1];    
    }
};