 #include <stdlib.h>
 #include <string.h>


 char *strclr(const char *s)
 {  
     int len = strlen(s);
     char *result = calloc(len + 1, sizeof(char));
     for(int i = 0; i < len; i++){
       result[i] = s[i];
       if (s[i] == '#'){
         result[i] = '\b';
         for(int j = i; j >= 0; j--){
           if (result[j] != '\b'){
             result[j] = '\b';
             break;
           }
         }
       }
     }
    
     int n = 0;
     for(int i = 0; i < len; i++){
       if (result[i] != '\b'){
         result[n++] = s[i];
       }       
     }
    
     for (; n < len; n++){
       result[n++] = '\0';
     }
        
     return result;
 }
