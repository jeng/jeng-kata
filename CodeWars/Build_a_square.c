 #include <stdlib.h>
 #include <stddef.h>

 char* generate_shape(size_t n) {
   if (n <= 0)
     return calloc(1, sizeof(char));   

   size_t bufsz = ((n + 1) * n);     
   char *res = calloc(bufsz, sizeof(char));
   memset(res, '+', bufsz-1);   
   for(size_t i = 1; i < n; i++)
     res[(i * n) + (i - 1)] = '\n';
     
   return res;
 }
