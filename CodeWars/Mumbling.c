 char *accum(const char *source){
   int n = strlen(source);
   char *r;
   int i = n;
   int sz = n-1;
   int k = 0;
   for(; i > 0; i--)
     sz += i;
   r = (char *)calloc(sz+1, sizeof(char));       
   for(i = 0; i < n; i++){
     for(int j = 0; j < i+1; j++){
       if (j == 0)
         r[k++] = toupper(source[i]);
       else
         r[k++] = tolower(source[i]);
     }
     if (i != n-1)
       r[k++] = '-';
   } 
   return r;
 }
