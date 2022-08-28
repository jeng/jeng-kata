 #include <cmath>

 class CaesarTwo
 {
 public:
     static char rotate(char c, int shift)
     {
         char offset = islower(c) ? 'a' : 'A';
         int idx = (c-offset) + shift;
         int nidx = 0;
         if (idx < 0)
             nidx = 26 - (abs(idx) % 26 );
         else
             nidx = idx % 26;
         return nidx+offset;
     }

     static std::vector<std::string> encodeStr(const std::string &s, int shift)
     {
         char k = tolower(s[0]);
         std::string key({k, rotate(k, shift)});
         auto buf = key + s;       

         for(int i = 2; i < buf.size(); i++)
             if (isalpha(buf[i]))
                 buf[i] = rotate(buf[i], shift);
                
         // I totally missed the obvious, floating point div then ceil.  Thanks micha1293
         int subsz = ceil(buf.size()/5.0);

         std::vector<std::string> res;
         for(int i = 0; i < buf.size(); i+=subsz)       
             res.push_back(buf.substr(i, subsz));       

         return res;
     }

     static std::string decode(std::vector<std::string> &s)
     {
         std::string buf = "";
         for(auto e : s)
             buf+=e;

         int shift = (buf[1] - buf[0]) * -1;

         for(int i = 2; i < buf.size(); i++)
             if (isalpha(buf[i]))
                 buf[i] = rotate(buf[i], shift);

         return buf.substr(2, buf.size());
     }

 };