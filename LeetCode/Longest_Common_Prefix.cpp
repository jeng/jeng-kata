class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //O(n * m)
        int i = 0;
        string pre ="";
        while (true) {
            if (strs.size() <= 0 ) break;
            if (i >= strs[0].size()) break;
            char lastChar = strs[0][i];
            for(int j = 0; j < strs.size(); j++){
                if (i > strs[j].size())
                    return pre;
                                if (strs[j][i] != lastChar)
                    return pre;
            }
            i++;
            pre += lastChar;
        }
        return pre;
    }
};