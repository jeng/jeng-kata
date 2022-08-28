 typedef unsigned long long ull;

 long double factln(int n){
   return lgammal(n + 1.0);
 }

 ull bico(int n, int k) {
   return llroundl(expl(factln(n) - factln(k) - factln(n-k)));
 }

 long long checkChoose(long long m, int n) {
   for(int i = 0; i < n; i++){
     if (bico(n, i) == m){
       return i;
     }
   }
   return -1;
 }
