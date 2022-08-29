class Solution {
public:
    int myAtoi(string s) {        
        int i = 0;
        bool negative = false;
        long long int result = 0;
                //Skip space
        for(; i < s.size() && s[i] == ' '; i++)
            ;
                //Do we have a leading sign?
        if (i < s.size()){
            if(s[i] == '-'){
                negative = true;
                i++;
            }
            else if (s[i] == '+'){
                i++;
            }
        }
                //Pull in the number
        for(; i < s.size() && '0' <= s[i] && s[i] <= '9'; i++){
            result *= 10;
            result += s[i] - '0';
                        //Clamp it
            if (negative && result * -1 < INT_MIN)
                return INT_MIN;
            else if (result > INT_MAX && !negative)
                return INT_MAX;
        }
                //Flip it if needed
        if (negative){            
            result *= -1;
            negative = false;
        }
                        return result;
    }
};