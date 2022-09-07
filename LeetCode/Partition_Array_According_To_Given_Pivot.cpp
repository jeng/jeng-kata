class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> result(nums.size());

        int startIndex = 0;
        int endIndex = nums.size() - 1;

        for(int i = 0, j = endIndex; i < nums.size(); i++,j--){
            if (nums[i] < pivot){
                result[startIndex++] = nums[i];
            }
            if (nums[j] > pivot){
                result[endIndex--] = nums[j];
            }
        }

        for(int i = startIndex; i <= endIndex; i++){
            result[i] = pivot;
        }

        return result;    
    }
};
