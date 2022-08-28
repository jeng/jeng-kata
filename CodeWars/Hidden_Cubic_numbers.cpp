 class Cubes
 {
 public:
   static bool isCubic(std::string s)
   {  
     if (s.size() <= 0)
       return false;
      
     int y = 0;
     for(char c : s)
     {
       int x = c-'0';
       y+=(x*x*x);     
     }
     return y == std::stoi(s);
   }
  
   static std::string formatResults(std::vector<int> &v)
   {
     if (v.size() == 0)
       return "Unlucky";
     else
     {
       int s = 0;
       std::string res = "";
       for(int x : v)
       {
         res += std::to_string(x) + " ";
         s += x;
       }
       res += std::to_string(s) + " ";
       return res + "Lucky";
     }
   }
  
   static std::string isSumOfCubes(std::string &str)
   {
     std::string t = "";
     int x=0;
     std::vector<int> v(0);   
    
     for(char c : str + "!")
     {
       if (isdigit(c) && x < 3)
       {
         t += c;
         x++;
       }
       else
       {
         if (isCubic(t))
           v.push_back(std::stoi(t));
         t = "";
         x = 0;
         if (isdigit(c))
         {
           t += c;
           x++;
         }
       }
     }
     return formatResults(v); 
   }
 };
