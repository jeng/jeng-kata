 #include <string>
 #include <vector>
 #include <iostream>
 std::string brainLuck(std::string code, std::string input)
 {
   int dataptr = 0;
   int codeptr = 0;
   int inputptr = 0;
   std::string output = "";
  
   auto mem = std::vector<int>();
   mem.push_back(0);
  
   while(codeptr < code.size()){
     switch(code[codeptr]){
       case '>': {
         dataptr++;
         if (dataptr >= mem.size())
           mem.push_back(0);
         break;         
       }
       case '<': {
         dataptr--;
         //TODO: handle < 0
         break;
       }
       case '+': {   
         mem[dataptr]++;
         mem[dataptr] = mem[dataptr] & 0xff;
         break;
       }
       case '-': {
         mem[dataptr]--;
         mem[dataptr] = mem[dataptr] & 0xff;
         break;
       }
       case '.': {       
         output += (char)mem[dataptr];       
         break;
       }
       case ',': {       
         mem[dataptr] = input[inputptr++];       
         if (mem[dataptr] < 0){         
           mem[dataptr] = 256 + mem[dataptr];
         }       
         //TODO: handle reading past input
         break;
       }
       case '[': {
         if (mem[dataptr] == 0) {
           int bc = 0;
           while ((code[++codeptr] != ']' || bc > 0) && codeptr < code.size()) {
             if (code[codeptr] == '[')
               bc++;
             else if (code[codeptr] == ']')
               bc--;           
           }
         }
         break;
       }
       case ']': {
         if (mem[dataptr] != 0) {
           int bc = 0;         
           while ((code[--codeptr] != '[' || bc > 0) && codeptr >= 0) {
             if (code[codeptr] == ']')
               bc++;
             else if (code[codeptr] == '[')
               bc--;           
           }
         }
         break;
       }
     } 
     codeptr++;
   }
   return output;
 }
