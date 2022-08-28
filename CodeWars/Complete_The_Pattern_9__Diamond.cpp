 std::string format(std::vector<std::string> &v)
 {
   std::string result = "";
   int i = 0;
   bool t = true;
   while(i >= 0)
   {
     result += v[t?i++:i--];
     if(i == v.size())
     {
       t = false;
       i = v.size()-2;
     }
     if(i != -1)
       result += "\n";
   }
   return result;
 }

 std::string pattern(int n)
 {
   if (n <= 0)
     return "";
    
   int m = n;
   int f = n-1;
   int w = m + f;
   std::vector<std::string> v(0);
   for(int i = 0; i < n; i++)
   {
     std::string s(w, ' ');
     int x = 0;
     for(int j = f--; j < m; j++)
     {
       x = (x+1)%10;
       s[j]='0'+x;
       s[(w-1)-j]='0'+x;
     }
     v.push_back(s);
   }   
   return format(v);
 }

