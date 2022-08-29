class Solution {
public:
    char open(char c){
        switch(c){
            case '}': return '{';
            case ')': return '(';
            case ']': return '[';
            default: return c;
        }
    }
    bool isValid(string s) {
        vector<char> stack;
        for(int i = 0; i < s.size(); i++){
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                stack.push_back(s[i]);
            else if (s[i] == ')' || s[i] == '}' || s[i] == ']'){
                if (stack.size() == 0){
                    return false;
                }else if (stack.back() != open(s[i])){
                    return false;
                }else{
                    stack.pop_back();
                }
            }
        }
        return stack.size() == 0;
            }
};