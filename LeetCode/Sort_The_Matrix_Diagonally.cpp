class Solution {
public:
    vector<int> extractDiagonal(vector<vector<int>> &mat, int row, int col){
        vector<int> result;
        for(int i = row, j = col; i < mat.size() && j < mat[i].size(); i++, j++){
            result.push_back(mat[i][j]); 
        }
        sort(result.begin(), result.end());
        return result;
    }
    
    void insertDiagonal(vector<vector<int>> &mat, 
                        int row, int col, 
                        vector<int> &diagonal){
        
        for(int i = row, j = col, k = 0; 
            i < mat.size() && j < mat[i].size() && k < diagonal.size();
            i++, j++, k++){
            mat[i][j] = diagonal[k]; 
        }
        
    }
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        for(int i = 0; i < mat[0].size(); i++){
            vector<int> diagonal = extractDiagonal(mat, 0, i);
            insertDiagonal(mat, 0, i, diagonal);
        }
        for(int i = 0; i < mat.size(); i++){
            vector<int> diagonal = extractDiagonal(mat, i, 0);
            insertDiagonal(mat, i, 0, diagonal);
        }
        return mat;
    }
};