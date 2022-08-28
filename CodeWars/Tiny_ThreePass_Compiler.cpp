 #include <queue>
 #include <vector>
 #include <string>
 #include <regex>
 #include <iostream>
 #include <algorithm>

 using namespace std;

 struct AST {
   AST(): a(nullptr), b(nullptr), n(0) {};
   AST(string op, int n): a(nullptr), b(nullptr), n(n), op(op) {};
   AST(string op, int n, AST *a, AST *b): a(a), b(b), n(n), op(op) {};
   AST(string op, AST *a, AST *b): a(a), b(b), n(0), op(op) {};
   string op;//+, -, *, /, i, a
   int n;
   struct AST *a;
   struct AST *b;
 };

 struct Compiler {

   vector <string> compile (string program) {
     return pass3 (pass2 (pass1 (program)));
   }

   // Turn a program string into a vector of tokens.  Each token
   // is either '[', ']', '(', ')', '+', '-', '*', '/', a variable
   // name or a number (as a string)
   vector <string> tokenize (string program) {
     static regex re ("[-+*/()[\\]]|[A-Za-z]+|\\d+");
     sregex_token_iterator it (program.begin (), program.end (), re);
     return vector <string> (it, sregex_token_iterator ());
   }

   bool is_number(const string& s) {
       string::const_iterator it = s.begin();
       while (it != s.end() && isdigit(*it)) ++it;
       return !s.empty() && it == s.end();
   }

   AST* factor(queue<string> &tokens, const vector<string> &args){
     if (tokens.size() == 0)
       return nullptr;

     string tmp = tokens.front();
     if (is_number(tmp)){
       tokens.pop();
       auto a = new AST();
       a->op = "imm";
       a->n = stoi(tmp);
       return a;
     }
     else if (tmp == "("){
       tokens.pop();
       auto ex = expression(tokens, args);
       tokens.pop(); //closing )
       return ex;
     }
     else{
       auto at = std::find(std::begin(args), std::end(args), tmp);
       if(at != args.end()){
         tokens.pop();
         auto a = new AST();
         a->op = "arg";
         a->n = at - args.begin();
         return a;
       }
     }
     return nullptr;
   }

   AST* term(queue<string> &tokens, const vector<string> &args){

     if (tokens.size() == 0)
       return nullptr;
    
     auto f = factor(tokens, args);

     while(tokens.size() > 0 && (tokens.front() == "*" || tokens.front() == "/")){
       if (tokens.front() == "*"){
         tokens.pop();
         auto a = new AST();
         a->op = "*";
         a->a = f;
         a->b = factor(tokens, args);
         f = a;
       }
       else if (tokens.front() == "/"){
         tokens.pop();
         auto a = new AST();
         a->op = "/";
         a->a = f;
         a->b = factor(tokens, args);
         f = a;
       }
     }

     return f;
   }

   AST* expression(queue<string> &tokens, const vector<string> &args){
     if (tokens.size() == 0)
       return nullptr;

     AST* t = term(tokens, args);

     while(tokens.size() > 0 && (tokens.front() == "+" || tokens.front() == "-")){
       if (tokens.front() == "+"){
         tokens.pop();
         auto a = new AST();
         a->op = "+";
         a->a = t;
         a->b = term(tokens, args);
         t = a;
       }
       else if (tokens.front() == "-"){
         tokens.pop();
         auto a = new AST();
         a->op = "-";
         a->a = t;
         a->b = term(tokens, args);
         t = a;
       }
     }

     return t;
   }

   AST* function(queue<string> &tokens) {
     tokens.pop();
     auto args = vector<string>();
     while(tokens.size() > 0 && tokens.front() != "]"){
       args.push_back(tokens.front());
       tokens.pop();
     }
     tokens.pop();
     return expression(tokens, args);
   }

   AST* parse(queue<string> &tokens){
     return function(tokens);
   }

   AST* reduce(AST *tree){
     if (tree == nullptr)
       return tree;
    
     if (tree->op == "imm" || tree->op == "arg")
       return tree;

     auto r_a = reduce(tree->a);
     auto r_b = reduce(tree->b);
     if (r_a != nullptr && r_a->op == "imm" && r_b != nullptr && r_b->op == "imm") {
       auto lh = r_a->n;
       auto rh = r_b->n;
       auto n = 0;
       switch(tree->op[0]){
         case '*': n = lh * rh; break;
         case '/': n = lh / rh; break;
         case '+': n = lh + rh; break;
         case '-': n = lh - rh; break;
       }
       tree->op = "imm";
       tree->n = n;
       delete tree->a;
       tree->a = nullptr;
       delete tree->b;
       tree->b = nullptr;
     }
     return tree;
   }


   queue<string> lexer(string s){
     string tok = "";
     queue<string> tokens;
     for(char c : s){
       switch(c){
         case '(':
         case ')':
         case '[':
         case ']':
         case '*':
         case '+':
         case '-':
         case '/':
           if (tok.size() > 0){
             tokens.push(tok);
             tok = "";
           }
           tok += c;
           tokens.push(tok);
           tok = "";
           break;
         case ' ':
           if (tok.size() > 0){
             tokens.push(tok);
             tok = "";
           }
           break;
         default:
           tok += c;
           break;
       }
     }

     if (tok != "")
       tokens.push(tok);

     return tokens;
   }

   bool is_arith(AST *tree){
     if (tree == nullptr)
       return false;

     return (tree->op == "*" ||
             tree->op == "/" ||
             tree->op == "-" ||
             tree->op == "+");
   }

   void ast_to_op(AST *tree, vector<string> &v){
  
     if (tree == nullptr)
       return;
    
     if (tree->op == "imm"){
       v.push_back("IM " + to_string(tree->n));
       return;
     }
  
     if (tree->op == "arg"){
       v.push_back("AR " + to_string(tree->n));
       return;
     }
  
     ast_to_op(tree->b, v);
  
     if (is_arith(tree->a)){
       v.push_back("PU");
       ast_to_op(tree->a, v);
     }
     else {
       v.push_back("SW");
       ast_to_op(tree->a, v);
     }
  
     if (is_arith(tree->a)){
       v.push_back("SW");
       v.push_back("PO");
       v.push_back("SW");
     }
  
     switch(tree->op[0]){
       case '*': v.push_back("MU"); break;
       case '/': v.push_back("DI"); break;
       case '+': v.push_back("AD"); break;
       case '-': v.push_back("SU"); break;
     }
   }
 
   // Returns an un-optimized AST
   AST *pass1 (string program) {
     auto tokens = lexer(program);
     return parse(tokens);
   }

   // Returns an AST with constant expressions reduced
   AST *pass2 (AST *ast) {
     return reduce(ast);
   }

   // Returns assembly instructions
   vector <string> pass3 (AST *ast){
     auto v = vector<string>();
     ast_to_op(ast, v);
     return v;
   }
 };

