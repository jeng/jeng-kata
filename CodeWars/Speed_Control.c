 int gps(int s, double* x, int sz) {
   int i = 0;
   double m = 0;
   for(i = 0; i < sz-1; i++)
   {
     double d = x[i+1] - x[i];
     if (d > m)
       m = d;
   }
   return (m * 3600)/s;
 }
