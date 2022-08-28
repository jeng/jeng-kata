 class Same {
     public :static bool comp(std::vector<int> a, std::vector<int> b)
     {     
       for(int i = 0; i < a.size(); i++)
         a[i] *= a[i];
      
       std::sort(a.begin(), a.end());
       std::sort(b.begin(), b.end());
       std::vector<int> res;
       std::set_difference(a.begin(), a.end(), b.begin(), b.end(), res.begin());
      
       return res.size() == 0;
     }
 };
