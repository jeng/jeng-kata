#include <unordered_map>
class Solution {
public:
    int romanToInt(string s) {
        std::unordered_map<char, int> umap;
        umap['I'] =    1;
        umap['V'] =    5;
        umap['X'] =   10;
        umap['L'] =   50;
        umap['C'] =  100;
        umap['D'] =  500;
        umap['M'] = 1000;
        int sum = 0;
        char last = ' ';
        for(int i = 0; i < s.size(); i++){
            if (last == ' '){
                sum = umap[s[i]];
            } else if (umap[last] < umap[s[i]]){
                //subtract
                sum -= (umap[last] * 2);
                sum += umap[s[i]];
            } else {
                sum += umap[s[i]];
            }
            last = s[i];
        }
        return sum;
    }
};