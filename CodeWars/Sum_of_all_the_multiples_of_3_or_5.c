 int findSum (int n){
   int i, r = 0;
   for (i = 3; i <= n; r += (i % 5) == 0 ? 0: i, i+=3);
   for (i = 5; i <= n; r += i, i+=5);
   return r;
 }
