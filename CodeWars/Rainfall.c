 #include <stdio.h>
 struct cda {
   char *c;
   float *m;
   struct cda *n;
 };

 typedef struct cda _c;
 #define N 12

 _c *p(char *s){
   int i = 0, j = 0;
   _c *cd = NULL;
   _c *t = NULL;

   for(;s[i] != '\0';i++){
     int n = 0;
     for(; s[i] != '\0' && s[i] != ':'; i++)
       n++;

     if (s[i] != ':'){
       fprintf(stderr, "No colon %d!\n", i);
       return NULL;
     }

     if (cd == NULL){
       cd = malloc(sizeof(_c));
       t = cd;
     }
     else {
       cd->n = malloc(sizeof(_c));
       cd = cd->n;
     }

     cd->n = NULL;
     cd->c = calloc(n+1, sizeof(char));

     for(j = 0; j < n; j++){
       cd->c[j] = s[(i-n) + j];
     }

     cd->m = calloc(N, sizeof(float));
     {
       int mi = 0;
       int spi = 0;
       do{
         i++;
         switch(s[i]){
           case ' ': spi = i; break;
           case '\n':
           case '\0':
           case ',': {
             int d = i - spi;
             int k = 0;
             int b = 0;
             int nm = 1;
             spi++;
             for(k = 0;k < d-1;k++){
               int u = s[spi+k] - '0';
               b=s[spi+k]=='.'||b;
               if (0 <= u && u <= 9){
                 cd->m[mi] *= 10;         
                 cd->m[mi] += s[spi+k] - '0';
                 nm = (b) ? nm*10: nm;
               }
             }
             cd->m[mi] = cd->m[mi]/nm;
             mi++;
           } break;
         }
       } while(s[i] != '\n' && s[i] != '\0');
     }
     if (s[i] == '\0')
       break;
   }
   return t;
 }

 double mean(char* s, char* t) { 
   _c *cd = p(s);
   while(cd != NULL){
     if (strcmp(cd->c, t) == 0){
       int i;
       float a = 0;
       for(i = 0; i < N; i++){
         a += cd->m[i];
       }
       return a/N;
     }     
     cd = cd->n;
   }
   return -1;
 }

 double variance(char* s, char* t) {
   _c *cd = p(s);
   while(cd != NULL){
     if (strcmp(cd->c, t) == 0){
       int i;
       float a = 0, b = 0;
       for(i = 0; i < N; i++){
         a += cd->m[i];
       }
       a /= N;
       for(i = 0; i < N; i++){
         float x = cd->m[i] - a;
         x*=x;
         b+=x;
       }
       return b/N;
     }     
     cd = cd->n;
   }
   return -1;
 }
