class Solution {
public:
    int playRobot(int n, int x, int y, string s, int idx){
        int result = 0;
        for(int i = idx; i < s.size(); i++){
            
            switch (s[i]){
                case 'L': x--; break;
                case 'R': x++; break;
                case 'U': y--; break;
                case 'D': y++; break;
            }
            
            if (x < 0 || x >= n || 
                y < 0 || y >= n) {
                return result;
            }
 
            result++;
        }        
        return result;        
    } 
    
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        vector<int> result;
        for(int i= 0; i < s.size(); i++){
            result.push_back(playRobot(n, startPos[1], startPos[0], s, i));
        }
        return result;
    }
};