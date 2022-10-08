class Solution {
public:
    void split(vector<int>& nums, vector<int> &positive, vector<int> &negative){
        for(int i = 0; i < nums.size(); i++){
            if (nums[i] >= 0){
                positive.push_back(nums[i]);
            } else {
                negative.push_back(nums[i]);
            }
        }
    }
        vector<int> merge(vector<int>& nums, vector<int>& positive, vector<int>& negative
        ){
        int posIdx = 0;
        int negIdx = 0;
        bool mergePositive = true;
        for(int i = 0; i < positive.size() + negative.size(); i++){
            if (mergePositive && posIdx < positive.size()){
                nums[i] = positive[posIdx++];
            }
                        if (!mergePositive && negIdx < negative.size()){
                nums[i] = negative[negIdx++];
            }
            mergePositive = !mergePositive;
        }
        return nums;
    }
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> positive;
        vector<int> negative;
        split(nums, positive, negative);
        merge(nums, positive, negative);
        return nums;
    }
};