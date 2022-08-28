 typedef struct pstr {
   int sz;
   char *p;
 } pstr; 

 typedef struct info {
   pstr s;
   int w;
 } info; 

 info *list;

 int name_size(char *st){
   int x = 0;
   int i = 0;
   for(; i < strlen(st); i++){
     if (st[i] == ',')
       x++;
   }
   return (i == 0) ? 0 : x + 1;
 }

 /* the last char of st cannot be ',' */
 int* unpack(char *st, int ns){
   int idx = 0;
   int i = 0;
  
   list = malloc(sizeof(info) * ns);
  
   list[idx].s.p = &(st[0]);
   list[idx].s.sz = 0;
   for(i = 0; i < strlen(st); i++){
     if(st[i] == ','){
       idx++;
       list[idx].s.p = &(st[i+1]);
       list[idx].s.sz = 0;
     }
     else{
       list[idx].s.sz++;
     }     
   }
 }

 void set_weight(int ns, int *we){
   for(int i = 0; i < ns; i++){
     info *fo = &(list[i]);   
     fo->w = fo->s.sz;
     for(int j = 0; j < fo->s.sz; j++){
       char c = tolower(fo->s.p[j]);
       int x = (c - 'a') + 1;     
       fo->w += x;           
     }
    
     fo->w *= we[i];   
   } 
 }

 static int comp(const void *p1, const void *p2)
 {
   info *fo1 = (info*)p1;
   info *fo2 = (info*)p2;
   if (fo1->w > fo2->w)
     return -1;
   else if (fo1->w == fo2->w){
     char *s1 = calloc(fo1->s.sz+1, sizeof(char));
     char *s2 = calloc(fo2->s.sz+1, sizeof(char));
     int x;
    
     strncpy(s1, fo1->s.p, fo1->s.sz);
     strncpy(s2, fo2->s.p, fo2->s.sz);
    
     x = strcmp(s1, s2);
    
     free(s1);
     free(s2);
    
     return x;
   }
   else   
     return 1;
 }

 char* nthRank(char* st, int* we, int n) {
   int x = 0;
   int ns = name_size(st);
   char *s;
   pstr *p;
  
   if (ns == 0)
     return "No participants";
   else if (n > ns)
     return "Not enough participants";
    
   unpack(st, ns);
   set_weight(ns, we);
   qsort(list, ns, sizeof(info), comp);
  
   p = &(list[n-1].s);
   s = calloc(p->sz+1, sizeof(char));
   strncpy(s, p->p, p->sz);
  
   return s;
 }
