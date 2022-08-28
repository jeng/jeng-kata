 #include <stdbool.h>
 #include <stddef.h>

 size_t partition_on(void *base, size_t nmemb, size_t size, bool(*predicate)(const void *))
 {
   int max = nmemb - 1;
   int i, j = 0;
   char *wp = (char *)base;
   void *x = (void *)malloc(size);

   for (i = 0; i < nmemb; i++) {
     if (predicate(wp + (j * size))) {
       int k = j;   
       memcpy(x, wp + (j * size), size);
       for (; k < max; k++) {
         memcpy(wp + (k * size), wp + ((k + 1) * size), size);
       }
       memcpy(wp + (max * size), x, size);    
     }
     else {
       j++;
     }
   }

   free(x);
   return j;
 }
