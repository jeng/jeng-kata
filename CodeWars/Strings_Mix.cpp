 #include <set>
 class CharCount
 {
     public:
         CharCount(char tag, char c, int count)
         {
             this->tag = tag;
             this->c = c;
             this->count = count;
         }
         char tag;
         char c;
         int count;
 };

 struct case_comp{
     bool operator()(const CharCount &rhs, const CharCount &lhs)
     {
         std::map<char, int> m = {{'1', 1}, {'2', 100}, {'=', 1000}};
         return (m[rhs.tag] * rhs.c) < (m[lhs.tag] * lhs.c);
     }
 };

 class Mix
 {
     private:
         static std::map<char, int> init()
         {
             std::map<char, int> result;
             for(char c = 'a'; c < 'z'; c++)
                 result[c] = 0;
             return result;
         }
        
         static std::map<char, int> get_count(const std::string &s)
         {
             std::map<char, int> result = init();
             for(auto c : s)
             {
                 if(islower(c))
                 {
                     result[c]++;
                 }
             }
             return result;
         }

         static void insert(std::map<int, std::set<CharCount,case_comp>> &m, int index, CharCount &c)
         {
             if (index <= 1)
               return;
              
             auto it = m.find(index);
             if (it == m.end())
                 m[index] = {c};
             else
                 m[index].insert(c);
         }

     public:
         static std::string mix(const std::string &s1, const std::string &s2)
         {
             auto s1m = get_count(s1);
             auto s2m = get_count(s2);
             std::map<int, std::set<CharCount,case_comp>> m;

             for(char c = 'a'; c <= 'z'; c++)
             {
                 bool same = s1m[c] == s2m[c];
                 if (s1m[c] == 0 && same)
                 {
                     continue;
                 }
                 else if (s1m[c] > s2m[c] || same)
                 {
                     auto cc = CharCount(same?'=':'1', c, s1m[c]);
                     insert(m, s1m[c], cc);
                 }
                 else
                 {
                     auto cc = CharCount('2', c, s2m[c]);
                     insert(m, s2m[c], cc);
                 }
             }

             std::stringstream ss;
             for(auto it = m.rbegin(); it != m.rend(); ++it)
             {
                 for(auto x: it->second)
                 {
                     if (ss.tellp() > 0)
                         ss << "/";
                     ss << x.tag << ":" << std::string(x.count, x.c);
                 }
             }
            
             return ss.str();
         }
 };

