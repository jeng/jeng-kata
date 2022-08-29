struct pos_t {
    int i;
    int j;
    int size;
};
class Solution {
public:
    bool isSquare(vector<vector<int>> &matrix, pos_t pos){
        for(int i = pos.i; i < pos.i + pos.size; i++){
            for(int j = pos.j; j < pos.j + pos.size; j++){
                if (i >= matrix.size()) {
                    return false;
                } else if (j >= matrix[i].size()) {
                    return false;
                } else if (matrix[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    int countSquares(vector<vector<int>>& matrix) {
        //init
        int count = 0;
        queue<pos_t> history;
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                if (matrix[i][j] == 1){
                    history.push({i, j, 2});
                    count++;
                }
            }
        }
        //search
        while(history.size() > 0){
            pos_t p = history.front();
            history.pop();
            if (isSquare(matrix, p)){
                history.push({p.i, p.j, p.size+1});
                count++;
            }
        }
        return count;    
    }
};