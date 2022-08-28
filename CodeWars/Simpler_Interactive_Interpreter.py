 import re
 import functools

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

     def assignment(self):       
         var = self.tokens.pop(0)
         self.tokens.pop(0)
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

     def factor(self):
         if len(self.tokens) == 0:
             raise expcetion("out of tokens")
         elif self.is_assignment():
             return assignment()
         elif is_number(self.tokens[0]):
             return float(self.tokens.pop(0))
         elif is_identifier(self.tokens[0]):
             return self.vars[self.tokens.pop(0)]
         elif self.tokens[0] == '(':
             self.tokens.pop(0)
             exp = self.expression()
             if len(self.tokens) > 0 and self.tokens[0] == ')':
                 self.tokens.pop(0)
                 return exp
             else:
                 raise Exception("Invalid expression")

     def input(self, expression):
         self.tokens = tokenize(expression)
      
         if len(self.tokens) == 0:
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
        
        
