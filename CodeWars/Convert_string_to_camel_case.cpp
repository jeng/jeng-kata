 #include <string>


 std::string to_camel_case(std::string s) {
     std::string res = "";
     char last = ' ';
     for(auto c : s)
     {
         if ((last == '_' || last == '-') && islower(c))
             res += toupper(c);
         else
             if (c != '_' && c != '-')
                 res += c;
         last = c;
     }
     return res;

 }
