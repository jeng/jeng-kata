class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        map<int, vector<int>> groups;
        vector<vector<int>> result;
        for(int i = 0; i < groupSizes.size(); i++){
            int size = groupSizes[i];
            if (groups.find(size) == groups.end()){
                vector<int> v;
                groups[size] = v;
                groups[size].push_back(i);
            } else {
                groups[size].push_back(i);
            }
            if (groups[size].size() == size) {
                result.push_back(groups[size]);
                vector<int> v;
                groups[size] = v;
            }
        }
        return result;
    }
};