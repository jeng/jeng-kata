 #include <stddef.h> // NULL

 int char_in_str(char c, char *delims){
   char *p = delims;
   while(*p != '\0'){
     if (*p == c)
       return 1;
     p++;
   }
   return 0;
 }

 char* my_strtok(char *src, const char *delims) {
   static char *start = NULL;
   char *p;
   char *res = NULL;
  
   if (src != NULL){
     start = src;
   }
  
   if (start == NULL){
     return NULL;
   }
    
   while(char_in_str(*start, delims)){
     start++;
   }   

   if (*start == '\0'){
     return NULL;
   }

   p = start; 
   while(*p != '\0' && !char_in_str(*p, delims)){   
     p++;   
   }
  
   if (*p == '\0'){
     res = start;
     start = p;
   }
   else{
     *p = '\0';
     res = start;
     start = p+1;
   }
  
   return res;
 }
