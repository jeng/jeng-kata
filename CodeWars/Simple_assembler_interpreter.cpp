 #include <iostream>

 #include <string>
 #include <unordered_map>

 enum ArgType {reg, value};

 struct Arg {
   ArgType type;
   int value;
   std::string reg;
 };

 struct Instruction {
   std::string mnemonic;
   Arg arg1;
   Arg arg2;
 };

 Instruction parse(std::string line) {
   std::vector<std::string> split;
   std::string s = "";
   Instruction ins;
   for (auto c = line.begin(); c != line.end(); ++c) {
     if (*c == ' ') {
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
  
   for (int i = 0; i < split.size(); i++) {
     switch (i) {
     case 0: ins.mnemonic = split[i]; break;
     case 1:
       if (isdigit(split[i][0]) || split[i][0] == '-') {
         ins.arg1.type = value;
         ins.arg1.value = std::stoi(split[i]);
       }
       else {
         ins.arg1.type = reg;
         ins.arg1.reg = split[i];//TODO instructions do not say what the limit is here
       }
       break;
     case 2:
       if (isdigit(split[i][0]) || split[i][0] == '-') {
         ins.arg2.type = value;
         ins.arg2.value = std::stoi(split[i]);
       }
       else {
         ins.arg2.type = reg;
         ins.arg2.reg = split[i];//TODO instructions do not say what the limit is here
       }
       break;

     default:
       std::cerr << "Invalid assembly line while parsing: " << line << std::endl;//TODO not secure but just practice
       break;
     }
   }
   return ins;
 }


 static int& getReg(std::unordered_map<std::string, int>& regs, std::string name)
 {
   return regs[name];
 }

 std::unordered_map<std::string, int> assembler(const std::vector<std::string>& program)
 {
   std::unordered_map<std::string, int> regs;

   int pc = 0;
   for (int pc = 0; pc < program.size();) {
     Instruction ins = parse(program[pc]);
     if (ins.mnemonic == "mov") {
       if (ins.arg1.type != reg) {
         std::cerr << "Invalid mov instruction" << std::endl;
         break;
       }
       int value = 0;
       if (ins.arg2.type == reg) {
         if (regs.count(ins.arg2.reg) == 0) {
           std::cerr << "Invalid mov instruction.  Reg " << ins.arg2.reg << " does not exist" << std::endl;
         }
         else {
           value = getReg(regs, ins.arg2.reg);
         }
       }
       else {
         value = ins.arg2.value;
       }
       if (regs.count(ins.arg1.reg) == 0) {
         regs.insert({ ins.arg1.reg, value });
       }
       else {
         regs[ins.arg1.reg] = value;
       }
       pc++;
     }
     else if (ins.mnemonic == "inc") {
       if (ins.arg1.type != reg) {
         std::cerr << "invalid inc instruction" << std::endl;
         break;
       }
       else {
         if (regs.count(ins.arg1.reg) == 0) {
           std::cerr << "invalid inc instruction.  Register invalid" << std::endl;
           break;
         }
         else {
           regs[ins.arg1.reg]++;
         }
       }
       pc++;
     }
     else if (ins.mnemonic == "dec") {
       if (ins.arg1.type != reg) {
         std::cerr << "invalid dec instruction" << std::endl;
         break;
       }
       else {
         if (regs.count(ins.arg1.reg) == 0) {
           std::cerr << "invalid dec instruction.  Register invalid" << std::endl;
           break;
         }
         else {
           regs[ins.arg1.reg]--;
         }
       }
       pc++;
     }
     else if (ins.mnemonic == "jnz") {
       int cmp = 0;
       if (ins.arg1.type == reg) {
         if (regs.count(ins.arg1.reg) == 0) {
           std::cerr << "invalid jnz instruction.  Register invalid" << std::endl;
           break;
         }
         else {
           cmp = regs[ins.arg1.reg];
         }
       }
       else {
         cmp = ins.arg1.value;
       }
      
       int pcDelta = 0;
       if (ins.arg2.type != value) {
         std::cerr << "invalid jnz. Second arg should be a constant" << std::endl;;
         break;
       }
       else {
         pcDelta = ins.arg2.value;
       }

       if (cmp != 0) {
         pc = pc + pcDelta;
       }
       else {
         pc++;
       }
     }
     else {
       std::cerr << "invalid op code" << std::endl;
       break;
     }
   }
   return regs;
 }
