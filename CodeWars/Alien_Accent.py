 import re
 def convert(st):
     return re.sub('a', 'o', re.sub("o", "u", st))

     * 2 years ago
     * Refactor
     * Discuss
   Beta
   Message from Alien (Easy Version)

        Python:

 def getnum(s, i):
     n = 0
     while i < len(s) and '0' <= s[i] <= '9':
         n *= 10
         n += int(s[i])
         i+=1
        
     return (n, i)       

 def inner(s, i):
     (repeat, i) = getnum(s, i)
     result = ""
     while(i < len(s) and s[i] != ']'):
         if s[i] == '[':
             (phrase, i) = inner(s, i+1)
             result += phrase
         else:           
             result += s[i]
             i+=1
     return (repeat * result, i+1)
                                        
 def unzip(s):
     i = 0
     result = ""
     while i < len(s):
         if s[i] == '[':
             (phrase, i) = inner(s, i+1)
             result += phrase
         else:
             result += s[i]
             i+=1
     return result           
            
