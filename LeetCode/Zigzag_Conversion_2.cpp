class Solution {
public:
    string convert(string s, int numRows) {
        char table[numRows * s.size()];
        bool filling = true;
                //Init
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < s.size(); j++){
                table[i * s.size() + j] = ' ';
            }            
        }
                //Fill the table
        int y = 0;
        int x = 0;
        for(auto c : s){
            if (filling){                
                table[y * s.size() + x] = c;
                y++;
                if (y >= numRows){
                    filling = false;
                    x++;
                    y = numRows - 2;
                    if (y <= 0){
                        y = 0;
                        filling = true;
                    }                        
                }
            }
            else {                
                table[y * s.size() + x] = c;
                x++;
                y--;
                if (y <= 0){
                    y = 0;
                    filling = true;
                }
            }
        }
                string result = "";
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < s.size(); j++){                
                char c = table[i * s.size() + j];
                //cout << c;
                if (c != ' ')
                    result += c;                
            }
            //cout << endl;
        }
        return result;    
    }
    };