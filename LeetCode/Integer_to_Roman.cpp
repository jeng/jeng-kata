class Solution {
public:
    unordered_map<char, int> umap;
    string roman(int con){        
        switch(con){
            case   4: return "IV";
            case   9: return "IX";
            case  40: return "XL";
            case  90: return "XC";
            case 400: return "CD";
            case 900: return "CM";                
        }
        string s = "MDCLXVI";
        int i = 0;
        string result = "";
        while(i < s.size() && con > 0){
            if (con >= umap[s[i]]){
                result += s[i];
                con -= umap[s[i]];
            } else {
                i++;
            }
        }        
        return result;
    }
        string intToRoman(int num) {
        umap['I'] =    1;
        umap['V'] =    5;
        umap['X'] =   10;
        umap['L'] =   50;
        umap['C'] =  100;
        umap['D'] =  500;
        umap['M'] = 1000;
                vector<string> stack;
                int place = 1;
        int n = 0;
        int con = 0;
        string result = "";
                while(num > 0){
            int n = num % 10;
            con = n * place;
            result = roman(con) + result;            
            place*=10;
            num = num/10;
        }
                        return result;
    }
};