class Solution {
public:
    int collectForTruck(char truck, vector<string>& garbage, vector<int>& travel){
        int travelTime = 0;
        int committedTime = 0;
        for (int i = 0; i < garbage.size(); i++){            
            for (int j = 0; j < garbage[i].size(); j++){
                if (garbage[i][j] == truck){
                    committedTime++;
                    committedTime += travelTime;
                    travelTime = 0;
                }
            }
            if (i < travel.size()){
                travelTime += travel[i];
            }
        }
        return committedTime;
    }
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        return collectForTruck('G', garbage, travel) + 
               collectForTruck('P', garbage, travel) + 
               collectForTruck('M', garbage, travel);
    }
};