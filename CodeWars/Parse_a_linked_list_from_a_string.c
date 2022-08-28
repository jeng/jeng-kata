 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>

 // "Preloaded Code" (do NOT modify!)
 typedef struct node {
   int data;
   struct node *next;
 } Node;

 int skip_space(char *string, int start, int end){
   for(; start < end; start++){
     if (string[start] != ' '){
       return start;
     }
   }   
 }

 int get_null(char *string, int start, int end){
   if (end - start < 4){
     fprintf(stdout, "Error parsing null\n");
     return -1;   
   }
   else if (
     string[start    ] == 'N' &&
     string[start + 1] == 'U' &&
     string[start + 2] == 'L' &&
     string[start + 3] == 'L'){   
     return start + 4;
   }
   else {
     fprintf(stdout, "Failed to parse NULL\n");
     return -1;
   }                 
 }

 int skip_arrow(char *string, int start, int end){
   if (end - start < 2){
     fprintf(stdout, "Error parsing arrow\n");
     return -1;
   }
   else if (
     string[start]     == '-' &&
     string[start + 1] == '>'){
     return start + 2;
   }
   else{
     fprintf(stdout, "Failed to parse arrow\n");
     return -1;
   }   
 }

 int get_token(char *string, int start, int end, int *token){
   int n = 0;
   *token = 0;
   for (; start < end; start++){
     if (isdigit(string[start])){     
       *token = ((*token) * 10) + (string[start] - '0');     
     }
     else {
       return start;
     }     
   }
 }

 Node *parse(char *string) {   
   int start = 0;
   int end = strlen(string) + 1;
   int token;
  
   Node *head = NULL;
   Node *working = NULL;
  
   while(start < end){   
     start = skip_space(string, start, end);
     if (start < 0)
       break;

     if (isdigit(string[start])){
       start = get_token(string, start, end, &token);
       if (working == NULL){
         working = malloc(sizeof(Node));
         head = working;
       }       
       else {
         working->next = malloc(sizeof(Node));
         working = working->next;
       }       
       working->data = token;
       working->next = NULL; 
     }
     else if (string[start] == 'N'){
       get_null(string, start, end);
       break;
     }
     else {
       fprintf(stdout, "invalid token at %d\n", start);
       break;
     }     
        
     start = skip_space(string, start, end);
     if (start < 0)
       break;
        
     start = skip_arrow(string, start, end);
     if (start < 0)
       break;
   }
  
   return head;
 }
