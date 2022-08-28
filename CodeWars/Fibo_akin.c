 #include <stdlib.h>

 int *lookup = NULL;
 //Let's see if we can allocate 1gb to memoize u
 #define MAX 268435456

 int u(int n) {
   int ans;
   if (lookup == NULL) {
     lookup = (int *)calloc(MAX, sizeof(int));
     lookup[1] = 1;
     lookup[2] = 1;
   }

   if (n < MAX && lookup[n] != 0)
     return lookup[n];

   ans = u(n - u(n - 1)) + u(n - u(n - 2));
   if (n < MAX)
     lookup[n] = ans;
  
   return ans;
 }

 int lengthSupUK(int n, int k) {
   int m = 0, i;
   for (i = 1; i <= n; i++) {
     if (u(i) >= k) m++;
   }
   return m;
 }

 int comp(int n) {
   int last = 0;
   int m = 0, i;
   for (i = 1; i <= n; i++) {
     if (u(i) < last) m++;
     last = u(i);
   }
   return m;
 }
