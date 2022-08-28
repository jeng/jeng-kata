 std::string makeline(int n)
 {
   int w = n + (n-1);
   int m = w - ((w-1)/2);
   int x = 0;
   std::string res = "";
   for(int i = 0; i < w; i++)
   {
     x = (i < m) ? (x+1)%10 : (((x-1)%10)+10)%10;
     res += x+'0';
   }
   return res;
 }

 std::string pattern(int n)
 {
   std::string res = "";
  
   if (n <= 0)
     return "";
  
   int m = n + (n-1);
   for(int i = 1; i <= n; i++)
   {
     int p = (m - (i + (i-1)))/2;
     std::string ps(p, ' ');
     if (res != "")
       res += '\n';
     res += ps + makeline(i) + ps;
   }
   return res;
 }
