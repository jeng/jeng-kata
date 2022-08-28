 #include <cmath>
 class Kata
 {
 public:
     std::vector<std::string> towerBuilder(int nFloors)
     {
         long w = (nFloors * 2) - 1;
         long x = std::ceil(w/2);
         long y = x;
         std::vector<std::string> v;
         std::string p(w, ' ');
         for(int i = 0; i < nFloors; i++)
         {
           p[x--] = '*'; p[y++] = '*';
           std::string s(p);
           v.push_back(s);
         }
         return v;       
     }
 };
