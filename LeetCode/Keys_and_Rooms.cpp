class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        queue<int> q;
        vector<bool> visited(rooms.size());
        q.push(0);        
        while(!q.empty()){
            int room = q.front();
            q.pop();
            if (!visited[room]){
                visited[room] = true;
                for(int i = 0; i < rooms[room].size(); i++){
                    q.push(rooms[room][i]);
                }
            }
        }
        for(int i = 0; i < visited.size(); i++){
            if (!visited[i])
                return false;
        }
        return true;        
    }
};