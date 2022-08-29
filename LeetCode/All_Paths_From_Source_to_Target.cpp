struct history {
    vector<int> path;
    int node;    
};
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
                //guaranteed to be a DAG so we don't need to worry about cycles
        //Need to record the path as we go
        queue<history> q;
        vector<vector<int>> result;
        history h;
        h.node = 0;
        q.push(h);
                while(q.size() > 0){
            h = q.front();
            q.pop();
            if (h.node == graph.size() -1){
                h.path.push_back(h.node);
                result.push_back(h.path);
            }
            for(int i = 0; i < graph[h.node].size(); i++){
                history h1;
                h1.node = graph[h.node][i];
                for(int j = 0; j < h.path.size(); j++){
                    h1.path.push_back(h.path[j]);
                }
                h1.path.push_back(h.node);
                q.push(h1);
            }            
        }
        return result;
    }
};