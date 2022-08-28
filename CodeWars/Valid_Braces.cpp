 bool valid_braces(std::string braces)
 {
     std::stack<char> st;
     std::map<char, char> m = {{'{','}'}, {'[', ']'}, {'(',')'}};
     for(auto c : braces)
     {
         if(m.find(c) == m.end())
         {
             if (st.empty())
                 return false;
             char d = st.top();
             st.pop();
             if (m.find(d) == m.end())
                 return false;
             else
                 if (m[d] != c)
                     return false;               
         }
         else
         {
             st.push(c);
         }
     }
     return true;
 }
