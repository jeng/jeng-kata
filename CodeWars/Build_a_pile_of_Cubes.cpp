 class ASum
 {
   public:
   static long long findNb(long long m)
   {
     long long x = 0;   
     while((m -= (++x*x*x)) > 0)   
       ;   
     return !m ? x : -1;
   }
 };
