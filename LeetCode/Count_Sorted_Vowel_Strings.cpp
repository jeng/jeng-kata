class Solution {
public:
    int countVowelStrings(int n) {
        //               a  e  i  o  u
        int history[] = {1, 1, 1, 1, 1};
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 5; j++){
                int n = 0;
                for (int k = j; k < 5; k++){
                    n += history[k];
                }
                history[j] = n;
            }
        }
        int result = 0;
        for(int i = 0; i < 5; i++){
            result += history[i];
        }
        return result;        
    }
};