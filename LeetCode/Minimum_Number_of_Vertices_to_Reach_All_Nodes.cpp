class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> incoming(n);
        for(int i = 0; i < edges.size(); i++){
            int from = edges[i][0];
            int to = edges[i][1];
            incoming[to]++;
        }
        vector<int> results;
        for(int i = 0; i < incoming.size(); i++){
            if (incoming[i] == 0)
                results.push_back(i);
        }
        return results;
    }
};