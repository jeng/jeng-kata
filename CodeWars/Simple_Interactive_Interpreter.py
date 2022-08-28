 import re

 def tokenize(expression):
     if expression == "":
         return []

     regex = re.compile("\s*(=>|[-+*\/\%=\(\)]|[A-Za-z_][A-Za-z0-9_]*|[0-9]*\.?[0-9]+)\s*")
     tokens = regex.findall(expression)
     return [s for s in tokens if not s.isspace()]

 def is_operator(token):
     return token in ['+', '-', '*', '/', '%']
        
 def is_identifier(token):
     return re.match("^(_|[A-Za-z])(_|[0-9A-Za-z])*$", token) != None

 def is_number(token):
     return re.match("^\d+(\.\d+)?$", token) != None

 class Interpreter:
     def __init__(self):
         self.vars = {}
         self.functions = {}

     def is_assignment(self):
         return len(self.tokens) > 2 and is_identifier(self.tokens[0]) and self.tokens[1] == '='
    
     def is_fn(self):
         return len(self.tokens) > 3 and self.tokens[0] == 'fn' and is_identifier(self.tokens[1])
        
     def function(self):
         if self.tokens[0] != 'fn':
             raise Exception("Invalid function")
        
         self.tokens.pop(0)
         name = self.tokens.pop(0)
        
         if name in self.vars:
             raise Exception("Attempt to assign function with existing var name")
        
         args = []
         while self.tokens[0] != '=>':
             a = self.tokens.pop(0)
            
             if a in args:
                 raise Exception("Duplicate arguments")
            
             args.append(a)

         self.tokens.pop(0) # move past =>
        
         body = []
         while len(self.tokens) > 0:
             #No global scope for variables
             tok = self.tokens.pop(0)
            
             if is_identifier(tok) and not tok in args:
                 raise Exception("Function expression has invalid arguments")
                
             body.append(tok)

         self.functions[name] = (args, body)       
    
     def assignment(self):       
         var = self.tokens.pop(0)
         if var in self.functions:
             raise Exception("Attempt to assign var with existing function name")
         self.tokens.pop(0) # move past =
         x = self.expression()
         self.vars[var] = x
         return x

     def expression(self):
         if len(self.tokens) > 0:
             f = self.factor()
             while len(self.tokens) > 0 and is_operator(self.tokens[0]):
                 op = self.tokens.pop(0)
                 if op == '+':
                     f = f + self.expression()
                 elif op == '-':
                     f = f - self.expression()
                 elif op == '*':
                     f = f * self.factor()
                 elif op == '/':
                     f = f / self.factor()
                 elif op == '%':
                     f = f % self.factor()
                 else:
                     raise Exception("Invalid operator")
            
             return f

     def eval_function(self, fn_name):
         args, body = self.functions[fn_name]
         replacement = {}
         for a in args:
             if len(self.tokens) == 0:
                 raise Exception("Invalid number of arguments")
             else:               
                 replacement[a] = str(self.expression())
        
         expression_body = []
         for tok in body:
             if tok in args:
                 expression_body.append(replacement[tok])
             else:
                 expression_body.append(tok)
        
         self.tokens = expression_body + self.tokens
        
         return self.expression()
        

     def factor(self):
         if len(self.tokens) == 0:
             raise expcetion("out of tokens")
         elif self.is_assignment():
             return self.assignment()
         elif is_number(self.tokens[0]):
             return float(self.tokens.pop(0))
         elif is_identifier(self.tokens[0]):
             if self.tokens[0] in self.vars:
                 return self.vars[self.tokens.pop(0)]
             elif self.tokens[0] in self.functions:
                 return self.eval_function(self.tokens.pop(0))
             else:
                 raise Exception("Unknown identifier")
         elif self.tokens[0] == '(':
             self.tokens.pop(0)
             exp = self.expression()
             if len(self.tokens) > 0 and self.tokens[0] == ')':
                 self.tokens.pop(0)
                 return exp
             else:
                 raise Exception("Invalid expression")
         else:
             raise Exception("Invalid factor")

     def input(self, expression):
         self.tokens = tokenize(expression)
      
         if len(self.tokens) == 0:
             return ''
      
         if self.is_fn():
             self.function()
             return ''
         if self.is_assignment():
             a = self.assignment()
             if len(self.tokens) == 0:
                 return a               
             else:
                 raise Exception("Invalid Input", "".join(self.tokens))       
         else:
             e = self.expression()
             if len(self.tokens) == 0:
                 return e               
             else:
                 raise Exception("Invalid Input", "".join(self.tokens))                       
        
