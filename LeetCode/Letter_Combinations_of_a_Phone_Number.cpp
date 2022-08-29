class Solution {
public:
        vector<string> appendString(string previous, vector<string> &list, int i){
        vector<string> result;
        if (i >= list.size()){
            if (previous.size() > 0)
                result.push_back(previous);
            return result;
        }        
                string working = list[i];        
        for(int j = 0; j < working.size(); j++){            
            vector<string> sub = appendString(previous + working[j], list, i+1);
            for (int k = 0; k < sub.size(); k++){
                result.push_back(sub[k]);
            }
        }
        return result;
    }
                vector<string> letterCombinations(string digits) {
        vector<string> result;
        map<char, string> lookup = {{'2', "abc"},
                       {'3', "def"},
                       {'4', "ghi"},
                       {'5', "jkl"},
                       {'6', "mno"},
                       {'7', "pqrs"},
                       {'8', "tuv"},
                       {'9', "wxyz"}};
        vector<string> list;
        for(int i = 0; i < digits.size(); i++){
            list.push_back(lookup[digits[i]]);
        }
        return appendString("", list, 0);                
    }
};