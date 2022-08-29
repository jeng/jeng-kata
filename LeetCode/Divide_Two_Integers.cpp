class Solution {
public:
    int64_t mul10(int64_t n){
        int x = n;
        for(int i = 0; i < 9; i++){
            n+=x;
        }
        return n;
    }
        int divide(int dividend, int divisor) {
        int64_t quotient = 0;
        int64_t n = dividend;
        int64_t d = divisor;
        vector<int64_t> scales;
        vector<int64_t> powers;
                int sign = 1;
        if (n < 0 && d < 0) {
            sign = 1;
            n = n - n - n;
            d = d - d - d;
        } else if (d < 0){
            sign = -1;
            d = d - d - d;
        } else if (n < 0){
            sign = -1;
            n = n - n - n;
        }
                if (d == 1){
            quotient = n;        
        }
        else {
            //lol
            int64_t x = 1;
            scales.push_back(d);
            powers.push_back(x);
                        while(n > d){
                if (n > d){
                    scales.push_back(d);
                    powers.push_back(x);
                } else {
                    break;
                }
                x =mul10(x);
                d =mul10(d);
            }
                        while(scales.size() > 0){
                d = scales.back();
                scales.pop_back();
                x = powers.back();
                powers.pop_back();                
                while(n >= d){
                    n = n - d;            
                    quotient+=x;
                }
            }
        }
                if (sign < 0)
            quotient = quotient - quotient - quotient;
                if (quotient > 2147483647)
            return 2147483647;
        else if (quotient < -2147483648)
            return -2147483648;
                    return quotient;        
    }
};