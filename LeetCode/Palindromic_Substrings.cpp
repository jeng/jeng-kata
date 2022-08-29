class Solution {
public:
    int IsPalindrom(string s, int start, int end){
    if (start < s.size() && end < s.size() && start <= end){
        while(start <= end){
            if (s[start] != s[end])
                return 0;       
            start++;
            end--;
        }
        return 1;
    } else {
            return 0;
        }
    }
        int countSubstrings(string s) {
        int n = s.size();
        vector<vector<int>> matrix;
        for(int i = 0; i < n; i++){
            vector<int> row(n);
            matrix.push_back(row);
        }
        matrix[0][0] = 1; //Since a single character is considered a palindrome
        for(int i = 0; i < n; i++){
            if (i > 0){
                matrix[i][i-1] = matrix[i-1][n-1];
            }
            for(int j = i; j < matrix[i].size(); j++){
                if( j > 0){
                    matrix[i][j] = matrix[i][j-1] + IsPalindrom(s, i, j);
                }
            }
        }
        return matrix[n-1][n-1];
    }
};