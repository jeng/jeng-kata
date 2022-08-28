 #include <string.h>

 void paren_swap(char *s, int i){
   char a = s[i];
   if (a == '(')
     a = ')';
   else if (a == ')')
     a = '(';
   s[i] = a;   
 }

 void swap(char *s, int i, int j){ 
   char t = s[i]; 
   s[i] = s[j];
   s[j] = t;
 }

 void reverse_between(char *s, int start, int end){
   int i = start, j = end;
   for(; i < j; i++, j--){
     swap(s, i, j);
     paren_swap(s, i);
     paren_swap(s, j);
   }
   if (i == j){
     paren_swap(s, i);
   }
 }

 int inner_reverse(char *s, int n){
   int end = n;
   for(int i = n; i < (int)strlen(s); i++){
     if (s[i] == '('){     
       i = inner_reverse(s, i+1);     
     }
     else if (s[i] == ')'){     
       end = i;
       break;
     }
   } 
   reverse_between(s, n, end - 1);
   return end;
 }

 char * reverse_in_parens(const char *text){
   // Hajime!
   char *result = (char*)strdup(text);
   for (int i = 0; i < (int)strlen(result); i++){
     if (result[i] == '('){
       i = inner_reverse(result, i+1);
     }
   } 
   return result;
 }
