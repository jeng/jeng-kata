 int divisors(long long n)
 {
   int r = 0;
   for(int i = 1; i <= n; i++)
     if (n % i == 0) r++;
   return r;
 }