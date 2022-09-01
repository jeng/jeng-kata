class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        vector<int> maxRow;
        vector<int> maxCol;
        for(int i = 0; i < grid.size(); i++){
            int mr = 0;
            for(int j = 0; j < grid[i].size(); j++){
                if (grid[i][j] > mr){
                    mr = grid[i][j];
                }
                if (i == 0){
                    maxCol.push_back(grid[i][j]);
                } else {
                    if (grid[i][j] > maxCol[j]){
                        maxCol[j] = grid[i][j];
                    }
                }
            }
            maxRow.push_back(mr);
        }
        
        int result = 0;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++){
                int delta = min(maxRow[i], maxCol[j]) - grid[i][j];
                result += delta;
            }
        }
        
        return result;
    }
};