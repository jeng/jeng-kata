struct Point {
    int x;
    int y;
};

struct Node {
    Point p;
    vector<Point> history;
};

class Solution {
    const int START = 1;
    const int ENDING = 2;
    const int OPEN = 0;
    const int BLOCKED = -1;
public:
    bool valid(Point p, vector<vector<int>> &grid){
        if (0 <= p.y && p.y < grid.size() &&
            0 <= p.x && p.x < grid[0].size()){
            if (grid[p.y][p.x] == BLOCKED){
                return false;
            }
        } else {
            return false;
        }
        return true;
    }
    
    bool inHistory(Point &p, Node &n){
        for(int i = 0; i < n.history.size(); i++){
            if (p.x == n.history[i].x && p.y == n.history[i].y){
                return true;
            }
        }
        return false;
    }
    
    int process(Node &last, 
                Point &newPoint, 
                vector<vector<int>> &grid, 
                queue<Node> &q,
                int openCount){
        
        if (valid(newPoint, grid)){
            if (grid[newPoint.y][newPoint.x] == ENDING) {

                if (last.history.size() == openCount)
                    return 1;
                
                return 0;
            }
            
            if (!inHistory(newPoint, last)){
                Node m;
                m.p = newPoint;
                m.history = last.history;
                m.history.push_back(last.p);
                q.push(m);
            }
        }
        return 0;
    }
    
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        queue<Node> q;
        //Find the start position
        Node start;
        int openCount = 0;
        for(int y = 0; y < grid.size(); y++){
            for(int x = 0; x < grid[y].size(); x++){
                if (grid[y][x] == START){
                    start.p.x = x;
                    start.p.y = y;
                } else if (grid[y][x] == OPEN) {
                    openCount++;
                }
            }
        }
        q.push(start);
        
        //BFS for each path
        int result = 0;
        while(!q.empty()){
            Node n = q.front();
            q.pop();
            Point up = {n.p.x, n.p.y-1};
            Point down = {n.p.x, n.p.y+1};
            Point left = {n.p.x-1, n.p.y};
            Point right = {n.p.x+1, n.p.y};
            result += process(n, up, grid, q, openCount);
            result += process(n, down, grid, q, openCount);
            result += process(n, left, grid, q, openCount);
            result += process(n, right, grid, q, openCount);
        }
        return result;
    }
};
