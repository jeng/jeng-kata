class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        for(int i = 1; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                if (j == 0){
                    int a = matrix[i-1][j]   + matrix[i][j];
                    int b = matrix[i-1][j+1] + matrix[i][j];                    
                    matrix[i][j] = min(a, b);
                } else if (j == matrix[i].size()-1){
                    int a = matrix[i-1][j-1] + matrix[i][j];
                    int b = matrix[i-1][j]   + matrix[i][j];
                    matrix[i][j] = min(a, b);
                } else {
                    int a = matrix[i-1][j-1] + matrix[i][j];
                    int b = matrix[i-1][j]   + matrix[i][j];
                    int c = matrix[i-1][j+1] + matrix[i][j];
                    matrix[i][j] = min(a, min(b, c));                
                }
            }
        }
        int result = matrix[matrix.size()-1][0];
        for(int i = 1; i < matrix[matrix.size()-1].size(); i++){
            result = min(matrix[matrix.size()-1][i], result);
        }
        return result;
    }
};