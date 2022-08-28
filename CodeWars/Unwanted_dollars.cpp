 using namespace std;

 double money_value(const string &s)
 {
   bool found_number = false;
   int ncount = 0;
   int dcount = 0;
   int pcount = 0;
   double d = 0;
   double mul = 10;
   for(auto c : s){
     if (c == ' ' && found_number)
       return d * ((ncount > 0) ? -1 : 1);
     else if (c == ' ')
       continue;
     else if (c == '$' && (found_number || dcount > 0))
       return 0.0;
     else if (c == '$' && dcount++ == 0)
       continue;
     else if (c == '-' && (found_number || ncount > 0))
       return 0.0;
     else if (c == '-' && ncount++ == 0)
       continue;
     else if (c == '.' && pcount > 0)
       return 0.0;
     else if (c == '.' && pcount++ == 0)
       mul = 1/10.0;
     else if ('0' <= c && c <= '9'){
       found_number = true;
       if (mul > 1){
         d *= mul;
         d += c-'0';
       } else {
         d += (c-'0') * mul;
         mul *= 0.1;       
       }     
     }
   }
   return d * ((ncount > 0) ? -1 : 1);
 }
