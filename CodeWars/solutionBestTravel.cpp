#include <algorithm>
#include <set>
class BestTravel
{
public:
    static int chooseBestSum(int t, int k, std::vector<int>& ls){
      int best = -1;
           
      std::vector<std::set<int>> table(t + 1);  

      for(auto i : ls){
        for(int j = t; j >= 0; j--){
          if (i == j){
            table[j].insert(1);
            if (k == 1){
              best = std::max(best, j);               
            }
          }            

          if (j - i >= 0){
            for(auto m : table[j-i]){
              if (m + 1 == k){
                best = std::max(best, j); 
              }
              if (m + 1 <= k){
                table[j].insert(m + 1);
              }
            }
          }
        }
      }
            
      return best;
    }
};