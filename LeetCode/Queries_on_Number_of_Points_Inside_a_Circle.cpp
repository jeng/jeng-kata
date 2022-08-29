class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries
        ) {
        vector<int> results(queries.size());
        for(int i = 0; i < queries.size(); i++){
            int x1 = queries[i][0];
            int y1 = queries[i][1];
            float r = queries[i][2];
            for(int j = 0; j < points.size(); j++){
                int x2 = points[j][0];
                int y2 = points[j][1];
                float d= sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
                if (d <= r){
                    results[i]++;
                }
            }
        }
        return results;
    }
};