class Solution {
public:
    int numberMoves(int bi, string boxes){
        int x = 0;
        for(int i = 0; i < boxes.size(); i++){
            if (i != bi){
                if (boxes[i] == '1'){
                    x += abs(bi - i);
                }
            }
        }
        return x;
    }
    vector<int> minOperations(string boxes) {
        vector<int> result;
        for(int i = 0; i < boxes.size(); i++){
            result.push_back(numberMoves(i, boxes));
        }
        return result;
    }
};