 int* parse(char* program)
 {
   int r = 0;
   int sz = 1;
   int *a = malloc(sizeof(int));
   for(int i = 0; i <= strlen(program); i++){   
     switch(program[i]){
       case 'i': r++; break;
       case 'd': r--; break;
       case 's': r = r * r; break;
       case 'o': {
         a[sz-1] = r;
         a = realloc(a, (++sz) * sizeof(int));
         break;
       }
     }     
   }
   return a;
 }
