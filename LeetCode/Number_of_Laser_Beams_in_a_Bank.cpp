class Solution {
public:
    int camerasInRow(vector<string>& bank, int row){
        int result = 0;
        for(int i = 0; i < bank[row].size(); i++){
            if (bank[row][i] == '1')
                result++;
        }
        return result;
    }
        int numberOfBeams(vector<string>& bank) {
        int pendingCameras = 0;
        int laserTotal = 0;
        for (int row = 0; row < bank.size(); row++){
            int cameraCount = camerasInRow(bank, row);
            if (cameraCount > 0){
                laserTotal += (pendingCameras * cameraCount);
                pendingCameras = cameraCount;
            }
        }
        return laserTotal;
    }
};