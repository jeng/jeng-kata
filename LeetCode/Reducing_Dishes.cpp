class Solution {
public:
    int maxSatisfaction(vector<int> &v){
        int winner = INT_MIN;
        bool firstpass = true;

        sort(v.begin(), v.end(), greater<int>());

        for(int i = v.size() - 1; i >= 0; i--){
            int k = 0;
            int result = 0;
            for(int j = i; j >= 0; j--){
                result += (j + 1) * v[k++];
            }
            if (firstpass) {
                winner = result;
                firstpass = false;
            } else if (result > winner){
                winner = result;
            }
        }
       
        if (winner < 0)
            return 0;

        return winner;
    }

};