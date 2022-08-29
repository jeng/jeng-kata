struct element_t {
    string s;
    int open;
    int closed;
};
class Solution {
public:
    bool balanced(string s){
        int n = 0;
        for(int i = 0; i < s.size() && n >= 0; i++){
            if (s[i] == '(')
                n++;
            else
                n--;
        }
        return (n == 0);
    }
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        queue<element_t> history;
        history.push({"(", 1, 0});
        while(history.size() > 0){
            element_t e = history.front();
            //cout << e.s << " " <<  e.open << " " << e.closed << endl;
            history.pop();
            element_t e2 = e;
            e.s += '(';
            e.open++;
            e2.s += ')';
            e2.closed++;
            if (e2.open == e2.closed && e2.open == n){
                if (balanced(e2.s)){
                    result.push_back(e2.s);
                }
            } 
            if (e.open <= n && e.closed <= n){
                history.push(e);
            } 
            if (e2.open <= n && e2.closed <= n){
                history.push(e2);
            }
        }
        return result;
    }
};