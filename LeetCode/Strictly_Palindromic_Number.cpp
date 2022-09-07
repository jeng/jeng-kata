class Solution {
public:
    bool isPalindrome(vector<int> s){
        int n = s.size()-1;
        for(int i = 0; i < s.size()/2; i++){
            if (s[i] != s[n--])
                return false;
        }
        return true;
    }
    
    vector<int> toBase(int n, int base){
        stack<int> stack;
        vector<int> num;
        while(n > 0){
            int remainder = n % base;
            n = n / base;
            stack.push(remainder);
        }
        while(!stack.empty()){
            num.push_back(stack.top());
            stack.pop();
        }
        return num;
    }
    
    bool isStrictlyPalindromic(int n) {
        for(int i = 2; i <= n -2; i++){
            vector<int> s = toBase(n, i);
            if (isPalindrome(s) == false){
                return false;
            }
        }
        return true;
    }
};
