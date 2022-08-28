 #include <string.h>
 #include <stdlib.h>
 #include <stdio.h>

 int len(char *strng) { 
   int n = 0;
   while(strng[n++] != '\n')
     ;
   return n-1;
 }

 void swap(char *strng, int i, int j){
   char tmp = strng[i];
   strng[i] = strng[j];
   strng[j] = tmp;   
 }

 char* vertMirror(char* strng) {
     char tmp;
     int i, ln = len(strng), j = 0;
     int blen = strlen(strng);
     while(j < blen) {
       for(i = 0; i < ln/2; i++){
         swap(strng, j + i, j + (ln-1) - i);     
       }
       j+=(ln + 1);
     }
     {
       char *res = calloc(blen, sizeof(char));
       strcpy(res, strng);
       return res;
     }
 }
 char* horMirror(char* strng) {
     int x, y, ln = len(strng);
     int blen = strlen(strng);
     char *res = calloc(blen, sizeof(char));
     strcpy(res, strng);
     for(x = 0; x < ln; x++) {
       for(y = 0; y < ln; y++){
         int i1 = (y * (ln + 1) + x);
         int i2 = (((ln-1) - y) * (ln + 1) + x);
         res[i1] = strng[i2];     
       }
     }
     return res;
 }
 typedef char* (*generic_func_t) (char*);
 char* oper(generic_func_t f, char* s) {
   return f(s);   
 }
