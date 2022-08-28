 typedef unsigned long long ull;

 long double factln(int n){
   return lgammal(n + 1.0);
 }

 ull bico(int n, int k) {
   return llroundl(expl(factln(n) - factln(k) - factln(n-k)));
 }

 ull diagonal(int n, int p)
 {
   ull result = 0;
   ull nCr = -1; 
   while(n >= 0 && nCr != 0){
     nCr = bico(n--, p);
     result += nCr;
   } 
   return result;   
 }
