 #include <string>

 class PlayPass
 {
   private:
   static char rollLetter(char c, int n)
   {
     char offset = '!';
    
     if ('a' <= c && c <= 'z')
       offset = 'a';
     else if ('A' <= c && c <= 'Z')
       offset = 'A';
      
     if (offset == '!')
       return c;
     else
       return (((c - offset) + n) % 26) + offset;
   }
  
   static char ninesComp(char n)
   {
     if('0' <= n && n <= '9')
       return (9-(n-'0'))+'0';
     return n;
   }
  
   public:
   static std::string playPass(const std::string &s, int n)
   {
     std::string res = "";
     int x = 0;
     for(auto c : s)
     {
       char d = ninesComp(rollLetter(c, n));
       res += (x++%2==0)?toupper(d):tolower(d);
     }
     std::reverse(res.begin(), res.end());
     return res;
   }
 };
