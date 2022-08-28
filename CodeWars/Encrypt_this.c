 char *encrypt_this(const char *str){
   char *sp = str;
   char *final = calloc(strlen(str) * 2 + 1, sizeof(char));
   char *fp = final;
   char *sl;
   char sn[4]; 
   int st = 0;
  
   while(1){
     if (*sp == ' ' || *sp == '\0'){
       if (st == 2){
         char t = *(fp-1);
         *(fp-1) = *sl;
         *sl = t;
       }
       if (*sp == '\0'){
         break;
       }
       st = 0;     
     }
     else if (st == 0){
       int i = 0;
       st = 1;

       if (*final != '\0'){
         *fp = ' ';
         fp++;
       }
      
       sprintf(sn, "%d", *sp);
      
       while(sn[i] != '\0'){
         *fp = sn[i++];
         fp++;
       }
     }
     else {
       if (st == 1){
         sl = fp;
         st = 2;
       }             
       *fp = *sp;
       fp++;
     }
     sp++;
   }
  
   return final;
 }
