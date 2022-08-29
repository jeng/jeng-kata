class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int widx = 0;        
        for(int i = 0; i < nums.size(); i++){
            if (nums[i] != val)                         
                nums[widx++] = nums[i];                            
        }
        return widx;
    }
};