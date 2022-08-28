 #include <cmath>
 class Carboat
 {

   public:
   static std::string howmuch(int a, int b)
   {
     int low = std::min(a,b);
     int high = std::max(a,b);
     std::string s= "[";
     for(int b = ceil((low-2)/7.0); b <= ceil((high-2)/7.0); b++)
     {
       double c = (1 + (7 * b)) / 9.0;
       double i;
       double f = modf(c, &i);
       double m = 1 + (9*c);
       if (f == 0 && m <= high)
       {       
         s += "[M: " + std::to_string((int)m) + " " +
               "B: " + std::to_string((int)b) + " " +
               "C: " + std::to_string((int)c) + "]";
       }
     }
     return s + "]";
   }
 };
