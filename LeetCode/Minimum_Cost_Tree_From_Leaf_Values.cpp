class Solution {
public:
    int mctFromLeafValues(vector<int>& ls) {
        int total = 0;
        while(ls.size() > 1){
            int min = INT_MAX;
            int minStartIdx = 0;
            for(int i = 1; i < ls.size(); i++){
                if ((ls[i-1] * ls[i]) < min){
                    min = ls[i-1] * ls[i];
                    minStartIdx = i-1;
                }
            }            
            total += min;
            if (ls[minStartIdx] < ls[minStartIdx+1]){
                ls.erase(ls.begin() + minStartIdx);
            } else {
                ls.erase(ls.begin() + (minStartIdx + 1));
            }
        }
        return total;
    }
};