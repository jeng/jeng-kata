 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>

 int charcount(char *s, char c){
     int n = 0;
     for(;*s != '\0';s++){
         if (*s == c)
             n++;
     }
     return n;
 }

 char **alloc_table(int len){
     char **table;
     int i;
     table = (char**)malloc(len * sizeof(char*));
     for(i = 0; i < len; i++){
         table[i] = (char*)calloc(len + 1, sizeof(char));
     }
     return table;
 }

 char **to_table(char *s, int *lines){
     char **table;
     int i = 0, j = 0, n = 0;
     int ln = strlen(s);
     *lines = charcount(s, '\n')+1;
     table = alloc_table(*lines);
     for(n = 0; n < ln; n++){
         if (s[n] == '\n'){
             i++;
             j=0;
         }
         else{
             table[i][j++] = s[n];
         }
     }
     return table;
 }

 void free_table(char **table, int len){
     while(--len >= 0)
         free(table[len]);
     free(table);
 }

 char **rot_90_counter(char **table, int lines){
     char **result = alloc_table(lines);
     int n = lines-1, i, j;
     for(i = 0; i < lines; i++)
         for (j = 0; j < lines; j++)
             result[i][j] = table[j][n-i];
     return result;
 }

 char **diag_to_sym(char **table, int lines){
     char **result = alloc_table(lines);
     int n = lines-1, i, j;
     for(i = 0; i < lines; i++)
         for (j = 0; j < lines; j++)
             result[i][j] = table[n-j][n-i];
     return result;
 }

 char *join_table(char **table, char delm, int lines){
     int sz = (lines+1)*lines;
     char *buffer = calloc(sz, sizeof(char));
     int n =0, i, j;
     for(i = 0; i < lines; i++){
         for (j = 0; j < lines; j++){
             buffer[n++] = table[i][j];
         }       
         if (n != sz-1)
             buffer[n++] = delm;
     }
     return buffer;
 }

 char *selfie_diag2_counterclock(char **table, int lines){
     char **diag  = diag_to_sym(table, lines);
     char **rot   = rot_90_counter(table, lines);
     int sz = (lines + 1) * lines * 3;
     char *result = calloc(sz, sizeof(char));
     int i;

     for (i = 0; i < lines; i++){
         strcat(result, table[i]);
         strcat(result, "|");
         strcat(result, diag[i]);
         strcat(result, "|");
         strcat(result, rot[i]);
         if (i != lines-1)
             strcat(result, "\n");
     }

     free_table(diag, lines);
     free_table(rot,  lines);
     return result;
 }

 char* diag2Sym(char* s) {   
     int lines;
     char **table = to_table(s, &lines);
     char **diag  = diag_to_sym(table, lines);
     char *result = join_table(diag, '\n', lines);
     free_table(table, lines);
     free_table(diag,  lines);
     return result;
 }

 char* rot90Counter(char* s) {
     int lines;
     char **table = to_table(s, &lines);   
     char **rot = rot_90_counter(table, lines);
     char *result = join_table(rot, '\n', lines);
     free_table(table, lines);
     free_table(rot,   lines);
     return result;
 }

 char* selfieDiag2Counterclock(char* s) {   
     int lines;
     char **table = to_table(s, &lines);
     char *result = selfie_diag2_counterclock(table, lines);
     free_table(table, lines);
     return result;
 }

 typedef char* (*generic_func_t) (char*);
 char* oper(generic_func_t f, char* s) {
   return f(s);
 }
