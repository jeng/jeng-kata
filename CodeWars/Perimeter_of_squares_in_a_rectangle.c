 typedef unsigned long long ull;
 ull perimeter(int n) {
   ull r = 1, o = 0, s = 0;
   int i = 0;
   while(i <= n){
     ull t = r;
     s += r;
     r += o;   
     o = t;
     i++;
   }
   return s * 4;
 }
