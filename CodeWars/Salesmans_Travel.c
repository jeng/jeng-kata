 #define SEP ','

 struct Pstr{
   char *s;
   int len;   
 };

 struct Addr{
   struct Pstr block;
   struct Pstr street;
   struct Pstr zip;
 };

 int sizeNeeded(char *orgr){
   int i = 0;
   int c = 1;
   for(i = 0; orgr[i] != '\0'; i++)
     if (orgr[i] == SEP)
       c++;
   return c;     
 }

 struct Addr* setZips(struct Addr *addrs, int sz){
   for(int i = 0; i < sz; i++){
     addrs[i].zip.len = 8;
     addrs[i].zip.s = &(addrs[i].block.s[addrs[i].block.len - 8]);
     addrs[i].block.len -= 9;
   }
   return addrs;
 }

 struct Addr* setBlocks(struct Addr *addrs, int sz){
   for(int i = 0; i < sz; i++){
     int streetSz = addrs[i].block.len;
     addrs[i].street = addrs[i].block;
     addrs[i].block.len = 0;
     for(int j = 0; j < streetSz; j++){
       addrs[i].street.s++;
       addrs[i].street.len--;
       if(('0' <= addrs[i].block.s[j] && addrs[i].block.s[j] <= '9')){
         addrs[i].block.len++;       
       }
       if(addrs[i].block.s[j] == ' '){
         break;
       }
     }
   }
   return addrs;
 }

 struct Addr* getAddresses(char *orgr, int sz){ 
   int start = 0;
   int n = 0;
   struct Addr *addrs;
  
   addrs = malloc(sizeof(struct Addr) * sz);
   addrs[n].block.s = orgr;
   addrs[n].block.len = 0;
  
   for(int i = 0; orgr[i] != '\0' && n < sz; i++){   
     if (orgr[i] == SEP){
       n++;
       addrs[n].block.s = &(orgr[i+1]);
       addrs[n].block.len = 0;
     }
     else {
       addrs[n].block.len++;
     }
   }   
  
   addrs = setZips(addrs, sz);
   addrs = setBlocks(addrs, sz);
  
   return addrs;
 }

 int pstrEqual(struct Pstr p1, struct Pstr p2){
   if (p1.len != p2.len)
     return 0;
   for(int i = 0; i < p1.len; i++){
     if (p1.s[i] != p2.s[i])
       return 0;
   }
   return 1;
 }

 char *pstrAppend(char *s, int *sz, struct Pstr pstr){
   int i = 0;
   int j = *sz;
   *sz = *sz + pstr.len;
   s = realloc(s, sizeof(char) * (*sz + pstr.len));
   for (i = 0; i < pstr.len; i++){
     s[j++] = pstr.s[i];
   }   
   return s;
 }

 struct Pstr cstrToPstr(char *s){
   struct Pstr pstr;
   pstr.s = s;
   pstr.len = 0;
   if (s){
     for(int i = 0; s[i] != '\0'; i++){
       pstr.len++;
     }
   }
   return pstr;
 }

 char* travel(char* orgr, char* zipcode) { 
   char *result = malloc(sizeof(char));
   int sz = sizeNeeded(orgr);
   int ressz = 0;
   int first = 1;

   struct Addr *addr = getAddresses(orgr, sz);
   struct Pstr zip = cstrToPstr(zipcode);
   struct Pstr colon = cstrToPstr(":");
   struct Pstr comma = cstrToPstr(","); 
   struct Pstr slash = cstrToPstr("/");
  
   char *snull = "\0";
   struct Pstr pnull;
   pnull.s = snull;
   pnull.len = 1;

   result = pstrAppend(result, &ressz, zip);
   result = pstrAppend(result, &ressz, colon);

   for(int i = 0; i < sz; i++){
     if (pstrEqual(addr[i].zip, zip)){     
      
       if(!first)
         result = pstrAppend(result, &ressz, comma);
        
       result = pstrAppend(result, &ressz, addr[i].street);     
       first = 0;
     }     
   }
      
   result = pstrAppend(result, &ressz, slash);
  
   first = 1;
   for(int i = 0; i < sz; i++){
     if (pstrEqual(addr[i].zip, zip)){     
      
       if(!first)
         result = pstrAppend(result, &ressz, comma);
        
       result = pstrAppend(result, &ressz, addr[i].block);

       first = 0;
     }     
   }

   free(addr);
  
   result = pstrAppend(result, &ressz, pnull);
  
   return result; 
 }
