class Solution {
public:
    int numSplits(string s) {
      int TOTAL = 26;
      int p1[27] = {0};
      int p2[27] = {0};
      int result = 0;
      int splitIdx = 1;
      //init
      int x = s[0] - 'a';
      p1[x]++;
      p1[TOTAL]++;
      for(int i = 1; i < s.size(); i++){
        x = s[i] - 'a';
        if (p2[x] == 0){
          p2[TOTAL]++;
        } 
        p2[x]++;
      }
      if (p1[TOTAL] == p2[TOTAL])
        result++;
      //run all splits
      for(int i = 1; i < s.size(); i++){
        int x = s[i] - 'a';
        if (p1[x] == 0){
          p1[TOTAL]++;
        }
        p1[x]++;
        p2[x]--;
        if(p2[x] == 0){
          p2[TOTAL]--;
        }
        if (p1[TOTAL] == p2[TOTAL])
          result++;
      }
      return result;
            }
};