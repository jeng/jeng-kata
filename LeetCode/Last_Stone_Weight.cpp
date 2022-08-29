class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> queue(stones.begin(), stones.end());                
        cout << queue.top() << endl;
        while(queue.size() > 1){
            int y = queue.top();
            queue.pop();
            int x = queue.top();
            queue.pop();
            if (x != y)
                queue.push(y - x);
        }
        if (queue.size() == 0)
            return 0;
        else
            return queue.top();
    }
};