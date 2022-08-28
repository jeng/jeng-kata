 #include <stdio.h>

 int strongest_even(int n, int m) {   
     int e = log2(m);
     int strongest = pow(2, e);
     if (n <= strongest && strongest <= m){
       return strongest;
     }
     else {
       strongest = pow(2, e);
       int tmp = strongest;
       for(int i = e-1; i >= 0; i--){
         strongest += pow(2, i);       
         if (n <= strongest && strongest <= m){
           return strongest;
         }
         else if (strongest > m){
           strongest = tmp;         
         }
         tmp = strongest;
         e--;
       }
     }
    
     return 0;
 }

     * 3 years ago
     * Refactor
     * Discuss

 #include <stdio.h>

 int strongest_even(int n, int m) {   
     int e = log2(m);
     int strongest = pow(2, e);
     if (n <= strongest && strongest <= m){
       return strongest;
     }
     else {
       strongest = pow(2, e);
       int tmp = strongest;
       for(int i = e-1; i >= 0; i--){
         strongest += pow(2, i);       
         if (n <= tmp && tmp <= m){
           return tmp;
         }
         else if (strongest > m){
           strongest = tmp;         
         }
         tmp = strongest;
         e--;
       }
     }
    
     return 0;
 }
