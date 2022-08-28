 #include <set>
 class WhichAreIn
 {

   public:
   static std::vector<std::string> inArray(std::vector<std::string> &array1, std::vector<std::string> &array2)
   {
     std::set<std::string> result;
     for(auto x : array1)
       for(auto y : array2)
         if (y.find(x) != std::string::npos)
           result.insert(x);
    
     std::vector<std::string> final;
     std::copy(result.begin(), result.end(), std::back_inserter(final));
    
     return final;
   }
 };
