 typedef struct pstr{
   char *p;
   long size;
 } pstr;

 /* n - a number of substrings */
 double pos_average(char *s, unsigned n)
 {
   pstr strings[n]; 
   int ln = strlen(s);
   int i = 0;
   int j = 0;
   int k = 0; 
   double score = 0;
   double outof = 0;
  
   /*split*/
   for(;i < ln; i++){
     if (isdigit(s[i])){
       strings[j].p = &(s[i]);
       strings[j].size = 0;
       for(;i < ln && isdigit(s[i]); i++, strings[j].size++)
         ;
       j++;/*TODO bounds check */
     }
   }
  
   /*compare*/ 
   for (i = 0; i < n; i++){
     for(j = i+1; j < n; j++){     
       if (strings[i].size != strings[j].size){
         printf("Invalid string size pstr[%d].size = %d pstr[%d].size = %d\n",
           i, strings[i].size, j, strings[j].size);
         return 0;
       }
       outof += strings[i].size;
       for(k = 0; k < strings[i].size; k++){
        
         if (strings[i].p[k] == strings[j].p[k]){
           score++;
         }
        
       }     
     }
   }
  
   return (score/outof) * 100;
 }
