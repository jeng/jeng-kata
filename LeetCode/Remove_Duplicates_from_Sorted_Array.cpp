class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //hmm, from the instructions we will have junk after the Kth element, weird
        int widx = 1;
        int last = 0;
        for(int i = 0; i < nums.size(); i++){
            if (i != 0){                
                if (last != nums[i]){
                    nums[widx++] = nums[i];                    
                }
            }
            last = nums[i];
        }
        return widx;
    }
};