 #include <iostream>

 #include <string>
 #include <unordered_map>

 enum ArgType { at_reg, at_value, at_string};

 const unsigned int EQ_FLAG = 0;
 const unsigned int LT_FLAG = 1;
 const unsigned int GT_FLAG = 2;

 struct Arg {
   ArgType type;
   int value;
   std::string reg;
   std::string str;
 };

 struct Instruction {
   std::string mnemonic;
   std::vector<Arg> args;
 };

 struct X5309 {
   //memory?
   std::unordered_map<std::string, int> regs;
   std::vector<int> stack;
   bool flags[3];
   int pc;
   std::vector<std::string> buffer;
   bool success;
 };

 std::string ltrim(std::string s) {
   int n = 0;
   for (int i = 0; i < s.size(); i++) {
     if (s[i] == ' ' || s[i] == '\t')
       n++;
     else
       break;
   }
   return s.substr(n, s.size());
 }

 std::string rtrim(std::string s) {
   int n = s.size();
   for (int i = s.size() - 1; i >= 0; --i) {
     if (s[i] == ' ' || s[i] == '\t')
       n--;
     else
       break;
   }
   return s.substr(0, n);
 }

 std::string trim(std::string s) {
   return rtrim(ltrim(s));
 }

 std::vector<std::string> breakLines(std::string line) {
   std::vector<std::string> split;
   std::string s = "";

   for (auto c = line.begin(); c != line.end(); ++c) {
     if (*c == '\n') {
       if (s.size() != 0)
         split.push_back(s);
       s = "";
     }
     else {
       s += *c;
     }
   }

   if (s.size() > 0)
     split.push_back(s);

   return split;
 }

 std::vector<std::string> tokenize(std::string line, char delimiter) {
   std::vector<std::string> split;
   std::string s = "";

   bool inString = false;
   for (auto c = line.begin(); c != line.end(); ++c) {  
     if (*c == '\'') {
       s += *c;
       if (inString) {      
         split.push_back(s);
         s = "";
         inString = false;
       }
       else {
         inString = true;       
       }
     }
     else if (inString) {
       s += *c;
     }
     else if (*c == delimiter) {
       if (s.size() != 0)
         split.push_back(s);
       s = "";
     }
     else {
       s += *c;
     }
   }

   if (s.size() > 0)
     split.push_back(s);

   return split;
 }

 std::vector<std::string> tokenize(std::string line) {
   return tokenize(line, ' ');
 }

 Instruction parse(std::string line) {
   Instruction ins;
   line = trim(line);
   int n = line.find(" ");
   if (n > -1) {
     ins.mnemonic = line.substr(0, n);
   }
   else {
     ins.mnemonic = line;
     return ins;
   }

   std::vector<std::string> args = tokenize(line.substr(n, line.size()), ',');

   for (int i = 0; i < args.size(); i++) {
     std::string arg = trim(args[i]);
     if (isdigit(arg[0]) || arg[0] == '-') {
       ins.args.push_back({ at_value, std::stoi(arg), "", "" });
     }
     else if (arg[0] == '\'') {
       //Assume well formed
       ins.args.push_back({ at_string, 0, "", arg.substr(1, arg.size() - 2) });
     }
     else {
       ins.args.push_back({ at_reg, 0, arg, "" });
     }
   }

   return ins;
 }

 static int& getReg(X5309 &x5309, std::string name)
 {
   return x5309.regs[name];
 }

 void assertArg(X5309 &x5309, ArgType argtype, ArgType expected, std::string message) {
   if (argtype != expected) {
     std::cout << message << std::endl;
     x5309.pc = INT_MAX; //exit;  
   }
 }

 void assertRegister(X5309 &x5309, std::string name) {
   if (x5309.regs.count(name) == 0) {
     std::cout << "register does not exist: " << name << std::endl;
     x5309.pc = INT_MAX; //exit;  
   }
 }

 int getRegOrValue(X5309 &x5309, Arg arg) {
   if (arg.type == at_reg) {
     assertRegister(x5309, arg.reg);
     return getReg(x5309, arg.reg);
   }
   else {
     return arg.value;
   }
 }

 void setReg(X5309 &x5309, std::string name, int value) {
   if (x5309.regs.count(name) == 0)
     x5309.regs.insert({ name, value });
   else 
     x5309.regs[name] = value;
 }

 //Do not call with empty lines
 void replaceAddressWithLabel(std::vector<std::string> &program) {
   //First pass pull out the labels with address
   std::unordered_map<std::string, int> labels;
   int pc = 0;
   for (auto line = program.begin(); line != program.end();) {
     std::vector<std::string> tokens = tokenize(*line);
     if (tokens[0][tokens[0].size() - 1] == ':') {
       std::string lbl = tokens[0].substr(0, tokens[0].size() - 1);     
       labels.insert({ lbl, pc });
       line = program.erase(line);
     }
     else {
       ++line;
       pc++;
     }
   }
   //Second pass update code with addresses
   for (auto line = program.begin(); line != program.end(); ++line) {
     std::vector<std::string> tokens = tokenize(*line);
     if (tokens[0] == "jmp" || tokens[0] == "je" || tokens[0] == "jne" || tokens[0] == "jge" ||
       tokens[0] == "jg" || tokens[0] == "jle" || tokens[0] == "jl" || tokens[0] == "call") {
       if (tokens.size() == 2 && labels.count(tokens[1])) {
         *line = tokens[0] + " " + std::to_string(labels[tokens[1]]);
       }
       else {
         std::cout << "invalid jump instruction " << *line << std::endl;
         exit(EXIT_FAILURE);
       }
     }
   }

 }

 std::vector<std::string> loadProgram(std::string program) {
   std::vector<std::string> lines = breakLines(program);
   for (auto line = lines.begin(); line != lines.end();) {
     int n = line->find(';');
     if (n > -1) {
       *line = line->substr(0, n);
     }
     *line = trim(*line);
     if (*line == "") {
       line = lines.erase(line);
     }
     else {
       ++line;
     }
   }
   replaceAddressWithLabel(lines);
   return lines;
 }


 X5309 assembler(const std::vector<std::string>& program)
 {
   X5309 x5309;
   x5309.success = false;
   x5309.pc = 0;
   for (; x5309.pc < program.size();) {
     Instruction ins = parse(program[x5309.pc]);
     if (ins.mnemonic == "mov") {
       assertArg(x5309,ins.args[0].type, at_reg, "Invalid mov instruction");
       int value = getRegOrValue(x5309, ins.args[1]);
       setReg(x5309, ins.args[0].reg, value);
       x5309.pc++;
     }
     else if (ins.mnemonic == "inc") {
       assertArg(x5309,ins.args[0].type, at_reg, "Invalid inc instruction");
       int value = getRegOrValue(x5309, ins.args[0]);
       setReg(x5309, ins.args[0].reg, value + 1);
       x5309.pc++;
     }
     else if (ins.mnemonic == "dec") {
       assertArg(x5309,ins.args[0].type, at_reg, "Invalid dec instruction");
       int value = getRegOrValue(x5309, ins.args[0]);
       setReg(x5309, ins.args[0].reg, value - 1);
       x5309.pc++;
     }
     else if (ins.mnemonic == "jmp") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jmp argument");
       x5309.pc = getRegOrValue(x5309, ins.args[0]);
     }
     else if (ins.mnemonic == "jne") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jne argument");    
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[EQ_FLAG]){
         x5309.pc++;
       }
       else {
         x5309.pc = newPc;      
       }
     }
     else if (ins.mnemonic == "je") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid je argument");     
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[EQ_FLAG]) {
         x5309.pc = newPc;
       }
       else {
         x5309.pc++;
       }
     }
     else if (ins.mnemonic == "jg") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jg argument");
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[GT_FLAG]) {
         x5309.pc = newPc;
       }
       else {
         x5309.pc++;
       }
     }
     else if (ins.mnemonic == "jl") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jl argument");
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[LT_FLAG]) {
         x5309.pc = newPc;
       }
       else {
         x5309.pc++;
       }
     }
     else if (ins.mnemonic == "jge") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jge argument");
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[GT_FLAG] || x5309.flags[EQ_FLAG]) {
         x5309.pc = newPc;
       }
       else {
         x5309.pc++;
       }
     }
     else if (ins.mnemonic == "jle") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid jle argument");
       int newPc = getRegOrValue(x5309, ins.args[0]);
       if (x5309.flags[LT_FLAG] || x5309.flags[EQ_FLAG]) {
         x5309.pc = newPc;
       }
       else {
         x5309.pc++;
       }
     }
     else if (ins.mnemonic == "add") {
       assertArg(x5309, ins.args[0].type, at_reg, "Invalid add instruction");
       int a = getRegOrValue(x5309, ins.args[0]);
       int b = getRegOrValue(x5309, ins.args[1]);
       setReg(x5309, ins.args[0].reg, a + b);//Overflow?  Doesn't look like we have a flag for that.
       x5309.pc++;
     }
     else if (ins.mnemonic == "sub") {
       assertArg(x5309, ins.args[0].type, at_reg, "Invalid sub instruction");
       int a = getRegOrValue(x5309, ins.args[0]);
       int b = getRegOrValue(x5309, ins.args[1]);
       setReg(x5309, ins.args[0].reg, a - b);//underflow?  Doesn't look like we have a flag for that.
       x5309.pc++;
     }
     else if (ins.mnemonic == "mul") {
       assertArg(x5309, ins.args[0].type, at_reg, "Invalid sub instruction");
       int a = getRegOrValue(x5309, ins.args[0]);
       int b = getRegOrValue(x5309, ins.args[1]);
       setReg(x5309, ins.args[0].reg, a * b);
       x5309.pc++;
     }
     else if (ins.mnemonic == "div") {
       assertArg(x5309, ins.args[0].type, at_reg, "Invalid sub instruction");
       int a = getRegOrValue(x5309, ins.args[0]);
       int b = getRegOrValue(x5309, ins.args[1]);
       setReg(x5309, ins.args[0].reg, a / b);//div by zero?
       x5309.pc++;
     }
     else if (ins.mnemonic == "cmp") {
       int a = getRegOrValue(x5309, ins.args[0]);
       int b = getRegOrValue(x5309, ins.args[1]);
       x5309.flags[LT_FLAG] = (a < b);
       x5309.flags[GT_FLAG] = (a > b);
       x5309.flags[EQ_FLAG] = (a == b);
       x5309.pc++;
     }
     else if (ins.mnemonic == "call") {
       assertArg(x5309, ins.args[0].type, at_value, "Invalid call argument");
       int newPc = getRegOrValue(x5309, ins.args[0]);     
       x5309.stack.push_back(x5309.pc + 1);
       x5309.pc = newPc;
     }
     else if (ins.mnemonic == "ret") {
       x5309.pc = x5309.stack.back();
       x5309.stack.pop_back();    
     }
     else if (ins.mnemonic == "end") {    
       x5309.success = true;
       x5309.pc = INT_MAX;
       //for (int i = 0; i < x5309.buffer.size(); i++) {
       //  std::cout << x5309.buffer[i] << std::endl;
       //}
     }
     else if (ins.mnemonic == "msg") {
       std::string s;
       for (int i = 0; i < ins.args.size(); i++) {
         if (ins.args[i].type == at_string) {
           s += ins.args[i].str;
         }
         else {
           s += std::to_string(getRegOrValue(x5309, ins.args[i]));
         }
       }
       x5309.buffer.push_back(s);
       x5309.pc++;
     }
     else {
       std::cout << "invalid op code" << program[x5309.pc] << std::endl;
       x5309.pc = INT_MAX;
     }
   }
   return x5309;
 }

 std::string assembler_interpreter(std::string program) {
   std::string s;
   X5309 x5309 = assembler(loadProgram(program));
   if (x5309.success) {
     for (int i = 0; i < x5309.buffer.size(); i++) {
       if (i > 0) {
         s += '\n';
       }
       s += x5309.buffer[i];
     }
     return s;
   }
   else {
     return "-1";
   }
 }
