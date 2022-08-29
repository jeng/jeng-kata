class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) 
            return 0;
        //"mississippi"
        //"issip"
        int i = 0;        
        for(; i < haystack.size();){            
            bool found = true;
            int idx = i;
            for(int j = 0; j < needle.size(); j++){
                if (haystack[i] == needle[j]){
                    i++;
                } else {
                    found = false;
                }
            }
            i = idx + 1;
            if (found){
                return idx;
            }
        }
        return -1;
    }
};