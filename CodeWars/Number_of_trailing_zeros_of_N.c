 long log5(long n) {
   return log10(n) / log10(5);
 }

 long zeros(long n) {
   long sum = 0;
   long kmax = log5(n);
   int k;
   for(k = 1; k <= kmax; k++){
     sum += n/pow(5, k);
   }   
   return sum;
 }
