class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        vector<int> xs;
        for(int i = 0; i < points.size(); i++){
            xs.push_back(points[i][0]);
        }
        sort(xs.begin(), xs.end());
        int maxDx = 0;
        int prevX = xs[0];
        for(int i = 0; i < xs.size(); i++){
            int dx = xs[i] - prevX;
            //cout << "i" << i << " dx " << dx << " xs " << xs[i] << " prev " << prevX << endl;
            maxDx = max(maxDx, dx);
            prevX = xs[i];
        }
        return maxDx;
    }
};