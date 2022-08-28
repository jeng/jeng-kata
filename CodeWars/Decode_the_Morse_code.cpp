 #include <stack>
 std::string decodeMorse(std::string morseCode) {   
     auto st = std::stack<std::string>();
     std::string current = "";
     int n = 0;
     for( auto p : morseCode ) {
       if (p == ' '){
         if (++n == 3){
           n = 0;
           if (st.size() > 0)
             st.push(" ");         
         }
         if (current != "")
           st.push(MORSE_CODE[current]);                 
         current = "";
       }
       else {
         n = 0;
         current += p;
       }
     }
     if (current != "")
       st.push(MORSE_CODE[current]);
    
     std::string result = "";             
    
     while(st.size() > 0) {     
       auto t = st.top();
       st.pop();
       if (t == " " && result.size() == 0)
         continue;     
      
       result = t + result;             
     }
     return result;
 }
