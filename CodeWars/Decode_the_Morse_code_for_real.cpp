 #include <math.h>
 class Decode{
 public:
     std::string symbol;
     int length;
     Decode(){};
     Decode(std::string symbol, int length): symbol(symbol), length(length) {};
     Decode(char bit, int length): symbol(bit == '1' ? "." : ""), length(length) {};
 };

 int max(int a, int b){
     if (a > b)
         return a;
     return b;
 }

 int min(int a, int b){
     if (a < b)
         return a;
     return b;
 }

 int distance(int a, int b){
     return abs(a-b);
 }

 std::string decodeBitsAdvanced(std::string st){   
     if (st.size() == 0)
         return "";

     auto start = st.begin();   

     //remove leading and trailing space
     while(start != st.end() && *start == '0'){
         ++start;
     }

     if (start == st.end()){
         return "";
     }

     auto end = st.end()-1;
     while(end != st.begin() && *end == '0'){
         --end;
     }
     end++;

     if (end == st.begin()){
         return "";
     }


     //init the symbol list with the size
     auto last = *start;
     int len = 0;
     auto syms = std::vector<Decode>();
     for(auto i = start; i != end; i++){
         if (*i != last){
             syms.push_back(Decode(last, len));
             last = *i;
             len = 0;
         }
         len++;
     }

     syms.push_back(Decode(last, len));

     //Compute the high and low range and the average
     int smallest = syms[0].length;
     int largest_on = syms[0].length;
     int smallest_on = syms[0].length;
     float space_avg = 0;
     float space_sum = 0;
     float space_count = 0;

     for(auto d: syms){
         if (d.symbol == "")
         {
             space_sum += d.length;
             space_count++;
         }
         smallest = min(d.length, smallest);
         if (d.symbol == ".") {
             largest_on = max(d.length, largest_on);
             smallest_on = min(d.length, smallest_on);
         }
     }

     space_avg = space_sum/space_count;
     space_avg = round(space_avg);

     //Adjust the symbols based on this range
     std::string result = "";
     for(auto d : syms){
         auto delta1 = distance(d.length, smallest);
         auto delta2 = distance(d.length, largest_on);
         if (d.symbol == ".") {
             if (largest_on == smallest)
               result += d.symbol;
             else if (delta1 < delta2)
               result += d.symbol;
             else
               result += "-";
         }
         else {
             if (d.length >= space_avg * 3)
                 result += "*";
             else if (d.length >= largest_on * 6)
                 result += "*";
             else if (d.length > largest_on * 3)               
                 result += " ";
             else if (delta1 < delta2)
                 result += "";
             else if (d.length == largest_on && largest_on == smallest)
                 result += "";
             else
                 result += " ";
         }
     }
     return result;
 }

 string decodeMorse (string morseCode) {   
     std::string result = "";
     std::string current = "";
     for(auto c : morseCode){   
         if (c == '*'){       
             result += morse_code[current];
             result += " ";
             current = "";
         }
         else if (c == ' '){         
             result += morse_code[current];
             current = "";
         }
         else {
             current += c;
         }
     }
     if (current != "")
         result += morse_code[current];       
     return result;
 }
