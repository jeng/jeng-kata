 char* group_by_commas(int n) {
   char *s = calloc(15, sizeof(n));
   char *tmp = calloc(15, sizeof(n));
   int cc = 0;
   while(n > 0){
     int x = n%1000;
     n = n/1000;
     if (cc > 0){
       if (n > 0)
         sprintf(tmp, "%.3d,%s", x, s);
       else
         sprintf(tmp, "%d,%s", x, s);
     }
     else {
       if (n > 0)
         sprintf(tmp, "%.3d", x);
       else
         sprintf(tmp, "%d", x);
     }
     sprintf(s, "%s", tmp);
     cc++;
   }
   return s;
 }
