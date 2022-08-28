 class SumSquaredDivisors
 {
 public:
     static std::string listSquared(long long m, long long n)
     {
       std::ostringstream u;
       u << "{";
       for(long long g = m; g <= n; g++)
       {
         long long l = 0;
         for(long long y = 1; y <= g; y++)
         {
           if((g%y)==0)
             l += (y*y);
         }
         long long ly = 0;
         long long x = 0;
         while(ly < l)
         {
           ly = (++x * x);
           if(ly == l)
           {
             if(u.tellp() > 1)
               u << ", ";
             u << "{" << g << ", " << ly << "}";
           }
         }
       }
       u << "}";
       return u.str();
     }
 };
