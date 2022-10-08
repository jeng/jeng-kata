class Solution {
public:
    int minOperations(int n) {
       int r = 0;
       for(int i = 0, j = n-1; i < j; i++, j--){
          r += (j-i); 
       } 
        return r;
    }
};