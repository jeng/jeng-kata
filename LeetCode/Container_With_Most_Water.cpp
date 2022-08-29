class Solution {
public:
    int maxArea(vector<int>& height) {
        int result = 0;
        int maxIdx = 0;
        for(int i = 0; i < height.size(); i++){
            int lastMaxIdx = maxIdx;
            int maxHeight = height[lastMaxIdx];
            for(int j = lastMaxIdx; j < height.size(); j++){
                int area = min(maxHeight, height[j]) * (j - lastMaxIdx);
                result = max(area, result);
                if (lastMaxIdx == maxIdx && height[j] > height[maxIdx])
                    maxIdx = j;
            }
            if (maxIdx == lastMaxIdx)
                return result;
        }
        return result;        
    }
};