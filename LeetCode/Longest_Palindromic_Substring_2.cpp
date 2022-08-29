class Solution {
public:
    string getString(string s, int size, int idx){
        string result = "";
        for(int i = idx, j = size; j > 0; i--, j--)
            result += s[i];
        return result;
    }
        bool isPalindrome(string s){
        string r = s;
        reverse(r.begin(), r.end());
        return r == s;
    }
        string longestPalindrome(string s) {
        vector<int> bucket[s.size() + 1];
        int size = s.size() * s.size();
        int tbl[size];
                for(int i = 0; i < size; i++)
            tbl[i] = 0;
        string r = s;
        reverse(r.begin(), r.end());
                int max_sub = 0;
                /* put the substrings in the correct buckets*/
        for(int i = 0; i < s.size(); i++){
            for(int j = 0; j < s.size(); j++){
                if(s[i] == r[j]){
                    if (i-1 >= 0 && j-1 >= 0){                        
                        int prev_size =  tbl[(i-1) * s.size() + (j-1)];              
                                                              tbl[i * s.size() + j] = prev_size + 1;
                                                if (prev_size + 1 > max_sub)
                            max_sub = prev_size + 1;
                                                bucket[prev_size + 1].push_back(j);
                    }
                    else{
                        tbl[i * s.size() + j] = 1;
                    }
                }
                else {
                    tbl[i * s.size() + j] = 0;
                }                
            }            
        }        
                /*Return a string from the first largest bucket that contains a palindrom*/
        for(int i = max_sub; i > 1; i--){
            if (bucket[i].size() > 0){
                for(auto j : bucket[i]){
                    string s = getString(r, i, j);
                    if (isPalindrome(s))
                        return s;
                }
            }
        }
                if (s.size() > 0){
            string result(1, s[0]);            
            return result;
        }
                return s;
    }
};