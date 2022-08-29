class Solution {
public:
    int twoEggDrop(int n) {
        int c = 1;
        while(n > 0){
            n = n - c;
            c = c + 1;
        }
        return c - 1;
    }
};