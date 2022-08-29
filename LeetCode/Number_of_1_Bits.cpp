class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t mask = 1;
        uint32_t r = 0;
        for(int i = 0; i < 32; i++){
            if (n & mask)
                r++;
            mask <<= 1;
        }
        return r;
    }
};