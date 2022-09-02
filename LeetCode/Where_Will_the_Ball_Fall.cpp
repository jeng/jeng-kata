class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        vector<int> balls(grid[0].size());
        vector<int> result(grid[0].size());
        
        for(int i = 0; i < grid[0].size(); i++){
            balls[i] = i;
            result[i] = -1;
        }
        
        for(int i = 1; i < grid.size() + 1; i++){
            vector<int> ballsPrime = balls;
            for(int j = 0; j < grid[0].size(); j++){
                ballsPrime[j] = -1;
                if (j-1 >= 0 && grid[i-1][j] == 1 && grid[i-1][j-1] == 1){
                    ballsPrime[j] = balls[j-1];
                }
                if (j + 1 < grid[0].size() && grid[i-1][j] == -1 && grid[i-1][j+1] == -1){
                    ballsPrime[j] = balls[j+1];
                }
            }
            balls = ballsPrime;
        }
        
        for(int i = 0; i < balls.size(); i++){            
            if (balls[i] >= 0){
                result[balls[i]] = i;
            }
        }
        return result;
    }
};
