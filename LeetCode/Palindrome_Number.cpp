class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = x;
        long t = 0;
        while(y > 0){
            int r = y % 10;
            y /= 10;
            t *= 10;
            t += r;            
        }        
        return x == t;
    }
};