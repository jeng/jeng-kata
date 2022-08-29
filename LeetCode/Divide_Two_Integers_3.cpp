class Solution {
public:
    int divide(int dividend, int divisor) {
        int64_t quotient = 0;
        int64_t n = dividend;
        int64_t d = divisor;
        vector<int64_t> scales;
        vector<int64_t> powers;
                int sign = 1;
        if (n < 0 && d < 0) {
            sign = 1;
            n *= -1;
            d *= -1;
        } else if (d < 0){
            sign = -1;
            d *= sign;
        } else if (n < 0){
            sign = -1;
            n *= sign;
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
                x *= 10;
                d *= 10;
            }
            while(scales.size() > 0){
                d = scales.back();
                scales.pop_back();
                x = powers.back();
                powers.pop_back();
                //cout << " d " << d << " x " << x << " n " << n << " q " << quotient 
                    << endl;
                while(n >= d){
                    n = n - d;            
                    quotient+=x;
                }
            }
        }
                quotient = sign * quotient;
        if (quotient > 2147483647)
            return 2147483647;
        else if (quotient < -2147483648)
            return -2147483648;
                    return quotient;        
    }
};