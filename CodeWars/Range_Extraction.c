 #include <stdlib.h>


 char *range_extraction(const *args, size_t n)
 {
   int *stack = malloc(sizeof(int) * n);
   char *s = calloc(1048576, sizeof(char));
   int sp = 0;
   for(int i = 0; i < n; i++){
     if (abs(stack[sp-1] - args[i]) > 1){
       if (sp > 2){
         char tmp[1024];
         sprintf(tmp,"%d-%d,", stack[0], stack[sp-1]);
         strncat(s, tmp, strlen(tmp));
         sp = 0;       
       }
       else {
         for(int j = 0; j < sp; j++) {
           char tmp[1024];
           sprintf(tmp, "%d,", stack[j]);
           strncat(s, tmp, strlen(tmp));
         }           
         sp = 0;           
       }
     }
     stack[sp++] = args[i];
   }
  
   if (sp > 2){
     char tmp[1024];
     sprintf(tmp,"%d-%d,", stack[0], stack[sp-1]);             
     strncat(s, tmp, strlen(tmp));     
   }
   else {   
     for(int j = 0; j < sp; j++){
       char tmp[1024];
       sprintf(tmp, "%d,", stack[j]);
       strncat(s, tmp, strlen(tmp));     
     }   
   }
  
   int ln = strlen(s);
   if (ln > 0){
     s[ln-1] = '\0';
   }
  
   return s;
 }
