class Solution {
public:
    int numTeams(vector<int>& numbers) {
        vector<vector<int>> table;
        vector<int> high(numbers.size());
        vector<int> low(numbers.size());
        table.push_back(low);
        table.push_back(high);
        int results = 0;
        for(int i = 0; i < numbers.size(); i++){
            for(int j = 0; j < i; j++){
                if (numbers[j] < numbers[i]) {
                    table[0][i]++;
                    if (i > 1){
                        results += table[0][j];
                    }
                }
                if (numbers[j] > numbers[i]) {
                    table[1][i]++;
                    if (i > 1){
                        results += table[1][j];
                    }
                }
            }
        } 
        return results;        
    }
};