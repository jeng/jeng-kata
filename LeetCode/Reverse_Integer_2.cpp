class Solution {
public:
    int reverse(int y) {
        long long u = 0;
        int sign = (y < 0) ? -1 : 1;
        long long x = (long)y * sign;
        while(x > 0){
            u *= 10;
            u += x % 10;
            x /= 10;
        }
        u *= sign;
        if (u > INT_MAX || u < INT_MIN)
            return 0;
        return u;
    }
};