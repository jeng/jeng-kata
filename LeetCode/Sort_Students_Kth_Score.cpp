#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct _greater
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

class Solution {
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {
        //Each row is a student
        //score[i][j] denotes ith students jth exam
        //We need to sort j by the kth column
        //
        // We could hash i by score that is O(n)
        // Sort by row O(nlogn())
        // The create the new matrix in the new order O(n)
        //
        // About a O(n logn()) algorithm

        unordered_map<int, int> lookup;
        vector<int> column;
        vector<vector<int>> result;
        int i = 0;
        for(auto v : score){
            column.push_back(v[k]);
            lookup[v[k]] = i++;
        }
        
        sort(column.begin(), column.end(), _greater());

        for(auto n : column){
            result.push_back(score[lookup[n]]);
        }

        return result;
    }
};

int main(){
    Solution s;
    vector<int> a;
    a.push_back(3);
    a.push_back(4);
    vector<int> b;
    b.push_back(5);
    b.push_back(6);
    vector<vector<int>> score;
    score.push_back(a);
    score.push_back(b);
    vector<vector<int>> result = s.sortTheStudents(score, 0);
    for(auto r: result){
        for(auto n : r){
            cout << n << " ";
        }
        cout << endl;
    }
    return 0;
}
