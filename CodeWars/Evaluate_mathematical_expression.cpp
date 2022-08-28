 #include <string>
 #include <stack>
 #include <iostream>

 typedef enum TokenType{
     START,
     END,
     ERR,
     NUM,
     MUL,
     DIV,
     ADD,
     SUB,
     LPAREN,
     RPAREN
 } TokenType;

 typedef struct Token{
     double value;
     TokenType type;
 } Token;

 typedef struct Environment{
     std::string expression;
     unsigned int index;
     std::stack<Token*> tokenStack;
 } Environment;

 void initEnvironment(Environment &environment, std::string &expression){
     environment.expression = expression;
     environment.index = 0;
     Token *token = new Token();
     token->value = 0;
     token->type = START;
     environment.tokenStack.push(token);
 }

 char currentChar(Environment &environment){
   return environment.expression[environment.index];
 }

 bool endOfExpression(Environment &environment){
   return (environment.index >= environment.expression.size());
 }

 bool isDigit(char c){
     return ('0' <= c && c <= '9');
 }

 Token *getNumber(Environment &environment){
   bool up = true;
     double result = 0;
     double n = 10;
   for(;
     !endOfExpression(environment) &&
     (currentChar(environment) == '.' || isDigit(currentChar(environment)));
     environment.index++)
     {
       if (currentChar(environment) == '.' && up){
         up = false;
       }
       else if (currentChar(environment) == '.' && !up){
                 Token *t = new Token();
                 *t = {0, ERR};
         return t;
       }
             else {
                 char c = currentChar(environment);
                 double digit = c - '0';
                 if (up){
                     result *= n;
                     result += digit;
                 }
                 else {
                     digit /= n;
                     n *= 10;
                     result += digit;
                 }
             }
     }
     Token *t = new Token();
     t->value = result;
     t->type = NUM;
     return t;
 }

 Token *initToken(TokenType tt){
     Token *result = new Token();
     result->value = 0;
     result->type = tt;
     return result;
 }

 Token *getToken(Environment &environment){
   if (endOfExpression(environment)){
     return initToken(END);
   }

   for(;
     !endOfExpression(environment) &&
         (currentChar(environment) == ' ' || currentChar(environment) == '\t');
     environment.index++)
     ;

   if (endOfExpression(environment)){
     return initToken(END);
   }

   switch(currentChar(environment)){
     case '*': environment.index++; return initToken(MUL);
     case '/': environment.index++; return initToken(DIV);
     case '+': environment.index++; return initToken(ADD);
     case '-': environment.index++; return initToken(SUB);
     case '(': environment.index++; return initToken(LPAREN);
     case ')': environment.index++; return initToken(RPAREN);
     default:
       char c = currentChar(environment);
       if (isDigit(c) || c == '.'){
         return getNumber(environment);
       }
       else {
         return initToken(ERR);
       }
   }
 }


 // I would normally write this type of calculator using recursive decent.
 // This time I wanted to explicitly manage the stack and minimize function calls
 double calc(std::string expression) {
     Environment environment;
     initEnvironment(environment, expression);

   Token *token;
     do{
     token = getToken(environment);
         if (token->type == ERR){
             break;
         }
         environment.tokenStack.push(token);
     }while(token->type != END);


   token = environment.tokenStack.top();
   environment.tokenStack.pop();

   //Reverse the token stack
   std::stack<Token*> tokenStack;
   while(token->type != START){
     tokenStack.push(token);
     token = environment.tokenStack.top();
     environment.tokenStack.pop();
   }
   tokenStack.push(token);

   //EVAL
   std::stack<Token*> evalStack;
   token = tokenStack.top();
   tokenStack.pop();
   int subPass = -1;
   int pass = 0;

   while(true){
     switch(token->type){
       case ADD:
       {
         if(pass == 1 || subPass == 1){
           Token *left = evalStack.top();
           evalStack.pop();
          
           if (left->type != NUM){
             std::cerr << "Invalid addition" << std::endl;
             return 0;
           }

           Token *right = tokenStack.top();
           tokenStack.pop();

           if (right->type != NUM){
             std::cerr << "Invalid addition" << std::endl;
             return 0;
           }
          
           right->value = left->value + right->value;
           //XXX should actually free left here
           evalStack.push(right);
         }
         else {
           evalStack.push(token);
         }
         break;
       }

       case SUB:
       {
         //prev current isNegative
         // num   -      F
         //  )    -      F
         //  (    -      T
         //  +    -      T
         //  *    -      T
         //  /    -      T
         //  -    -      T
         //start  -      T
         //end    -      F
         TokenType lastType = evalStack.top()->type;
         if (lastType == SUB || lastType == ADD || lastType == MUL ||
           lastType == DIV || lastType == START || lastType == LPAREN){
          
           if (tokenStack.top()->type == NUM){
             token->type = NUM;
             token->value = tokenStack.top()->value * -1;
             tokenStack.pop();
             tokenStack.push(token);
             tokenStack.push(evalStack.top());
             evalStack.pop();
             break;
           }
          
         }

         if(pass == 1 || subPass == 1){
           Token *left = evalStack.top();
           evalStack.pop();
          
           if (left->type != NUM){
             std::cerr << "Invalid addition" << std::endl;
             return 0;
           }

           Token *right = tokenStack.top();
           tokenStack.pop();

           if (right->type != NUM){
             std::cerr << "Invalid addition" << std::endl;
             return 0;
           }
          
           right->value = left->value - right->value;
           //XXX should actually free left here
           evalStack.push(right);
         }
         else {
           evalStack.push(token);
         }
         break;
       }

       case MUL:
       {
         Token *left = evalStack.top();
         evalStack.pop();
        
         if (left->type != NUM){
           std::cerr << "Invalid multiply" << std::endl;
           return 0;
         }

         Token *right = tokenStack.top();
         tokenStack.pop();

         if (right->type == NUM){
           right->value = left->value * right->value;
           evalStack.push(right);
         }
         else {
           tokenStack.push(right);
           evalStack.push(left);
           evalStack.push(token);
         }
         break;
       }

       case DIV:
       {
         Token *left = evalStack.top();
         evalStack.pop();
        
         if (left->type != NUM){
           std::cerr << "Invalid multiply" << std::endl;
           return 0;
         }

         Token *right = tokenStack.top();
         tokenStack.pop();

         if (right->type == NUM){
           if (right->value == 0){
             std::cerr << "Divide by zero" << std::endl;
             return 0;
           }
           right->value = left->value / right->value;
           evalStack.push(right);
         }
         else {
           tokenStack.push(right);
           evalStack.push(left);
           evalStack.push(token);
         }
         break;
       }

       case LPAREN:
       case START:
       case NUM:
         evalStack.push(token);
         break;

       case RPAREN:
       {
         //Unwind to the starting paren and eval
         if (subPass == -1 || subPass == 0){
           subPass = subPass + 1;
           evalStack.push(token);
           while(evalStack.size() > 0 && evalStack.top()->type != LPAREN){
             tokenStack.push(evalStack.top());
             evalStack.pop();
           }
           if (evalStack.top()->type != LPAREN){
             std::cerr << "Invalid subexpression" << std::endl;
             return 0;
           }
           tokenStack.push(evalStack.top());
           evalStack.pop(); 
         }
         else{
           std::stack<Token*> currentLocation;
           Token *result = evalStack.top();
           evalStack.pop();
           evalStack.pop(); //pop the lparen
           Token *symbol = evalStack.top();
           evalStack.pop();
           tokenStack.push(result);
           tokenStack.push(symbol);
           subPass = -1;
         }
         break;
       }

       case END:
       {
         if (pass == 0){
           //The first pass is done.
           //unwinded the stack and evaluate addition and subtraction
           pass = 1;
          
           evalStack.push(token);//push the end token
           while(evalStack.size() > 0){
             tokenStack.push(evalStack.top());
             evalStack.pop();
           }
         }
         break;
       }
     }

     if (tokenStack.size() == 0){
       break;
     }
     else{
       token = tokenStack.top();
       tokenStack.pop();
     }
   }

   if (evalStack.size() < 2)//Should have the start token and the result
   {
     std::cerr << "invalid expression" << std::endl;
     return 0;
   }

   Token *result = evalStack.top();
     return result->value;
 }
