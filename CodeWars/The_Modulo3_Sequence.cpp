 int sequence(int n)
 {
   int a[] = {0,1,1,2,0,2,2,1};
   return a[(n-1)%8];
 }

     * 5 years ago
     * Refactor
     * Discuss

 int sequence(int n)
 {
   int a[8] = {0,1,1,2,0,2,2,1}; 
   return a[(n-1)%8];
 }
