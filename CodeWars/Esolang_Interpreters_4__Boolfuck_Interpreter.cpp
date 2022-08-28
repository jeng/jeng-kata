 #include <cstdlib>
 #include <iostream>
 #include <cstring>

 int* char_to_bits(int c){
   int *result = (int*)malloc(8 * sizeof(int));
   int mask = 1 << 7;
   for(int i = 0 ; i < 8; i++){
     int r = c & mask;
     r = r >> (7-i);
     result[7-i] = r;   
     mask = mask >> 1;
   }
   return result;
 }

 int bits_to_char(int *bits){
   int r = 0;
   for(int i = 0; i < 8; i++){
     r = r | (bits[i] << i);
   }
   return r;
 }

 struct Byte {
   int c;
   int *bits;
   struct Byte *next;
   struct Byte *prev;
 };

 struct Byte *init_byte_list(const char *s){
   int len = strlen(s);
   struct Byte *byte_list = NULL;
   struct Byte *top = NULL;
   for(int i = 0; i <= len; i++){
     if (byte_list == NULL){
       byte_list = (struct Byte*)malloc(sizeof(struct Byte));
       byte_list->prev = NULL;
       top = byte_list;
     }
     else {
       byte_list->next = (struct Byte*)malloc(sizeof(struct Byte));
       byte_list->next->prev = byte_list;
       byte_list = byte_list->next;
     }
     byte_list->c = s[i];
     byte_list->bits = char_to_bits(s[i]);
     byte_list->next = NULL;
   }
   return top;
 }

 char *boolfuck (const char *code, const char *input) {
   struct Byte *inputptr = init_byte_list(input);
   int codesize = strlen(code) + 1;
   int codeptr = 0;
   int inputbit = 0;
   int membit = 0;
   int outputbit = 0;
   struct Byte *outputptr = (struct Byte*)malloc(sizeof(struct Byte));
   struct Byte *memptr = (struct Byte*)malloc(sizeof(struct Byte));
   memptr->c = 0;
   memptr->bits = char_to_bits(memptr->c);
   memptr->next = NULL;
   memptr->prev = NULL;

   outputptr->c = 0;
   outputptr->bits = char_to_bits(outputptr->c);
   outputptr->next = NULL;
   outputptr->prev = NULL;

  
   for(;codeptr < codesize;codeptr++){
     switch(code[codeptr]){
       case '>':{
         membit++;       
         if (membit > 7) {
           membit = 0;
           if (memptr->next == NULL){
             memptr->next = (struct Byte*)malloc(sizeof(struct Byte));
             memptr->next->prev = memptr;
             memptr = memptr->next;
             memptr->c = 0;
             memptr->bits = char_to_bits(memptr->c);
             memptr->next = NULL;
           }
           else {
             memptr = memptr->next;
           }
         }
         break;
       }
       case '<':{
         membit--;
         if (membit < 0){
           membit = 7;
           if (memptr->prev == NULL){
             memptr->prev = (struct Byte*)malloc(sizeof(struct Byte));
             memptr->prev->next = memptr;
             memptr = memptr->prev;
             memptr->c = 0;
             memptr->bits = char_to_bits(memptr->c);
             memptr->prev = NULL;
           }
           else {
             memptr = memptr->prev;
           }
         }
         break;
       }
       case '+':{
         memptr->bits[membit] ^= 1;
         break;
       }
       case ',':{
         int r = 0;
         if (inputbit > 7){
           inputbit = 0;
           if (inputptr->next != NULL){
             inputptr = inputptr->next;
             r = inputptr->bits[inputbit];
           }
         }
         else {
           if (inputptr != NULL){
             r = inputptr->bits[inputbit];
           }
         }
         memptr->bits[membit] = r;
         inputbit++;
         break;
       }
       case ';': {
         if (outputbit > 7){
           outputbit = 0;
           outputptr->next = (struct Byte*)malloc(sizeof(struct Byte));
           outputptr->next->prev = outputptr;
           outputptr = outputptr->next;
           outputptr->c = 0;
           outputptr->bits = char_to_bits(outputptr->c);
           outputptr->next = NULL;
         }
         outputptr->bits[outputbit++] = memptr->bits[membit];
         break;
       }
       case '[': {
         if (memptr->bits[membit] == 0) {
           int bc = 0;
           while ((code[++codeptr] != ']' || bc > 0) && codeptr < codesize) {
             if (code[codeptr] == '[')
               bc++;
             else if (code[codeptr] == ']')
               bc--;           
           }
         }
         break;
       }
       case ']': {
         int bc = 0;         
         while ((code[--codeptr] != '[' || bc > 0) && codeptr >= 0) {
           if (code[codeptr] == ']')
             bc++;
           else if (code[codeptr] == '[')
             bc--;           
         }
         //Go back one more so that we run [ again
         codeptr--;
         break;
       }
     }
   }
  
   struct Byte *worker = outputptr;
   int size = 1;
   //rewind
   while (worker->prev != NULL){
     worker = worker->prev;
     size++;
   }
  
   char *result = (char*)calloc(size+1, sizeof(char));
   for(int i = 0; i < size; i++, worker = worker->next){
     result[i] = bits_to_char(worker->bits);
   }

   return result;
 }

