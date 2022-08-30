class Solution {
public:
    int minPartitions(string n) {
        int res = 0;
        for(int i = 0; i < n.size(); i++){
            int x = n[i] - '0';
            res = max(x, res);
        }
        return res;
    }
};
