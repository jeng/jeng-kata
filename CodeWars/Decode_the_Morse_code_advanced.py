 import sys

 def leadingZeros(bits):
     n = 0
     for x in bits:
         if x == '0':
             n += 1
         else:
             return n
     return n
    
    
 def findMin(bits, d):   
     m = sys.maxint
     n = 0
     for x in bits:
         if x == d:           
             n+=1
         else:           
             if n > 0:
                 m = min(n, m)
                 n = 0
            
     if m == sys.maxint:           
         return n
     else:
         return m
    


 def getSym(long, state):
     if state == '1':
         if long:
             return '-'
         else:
             return '.'
     else:
         if long:
             return ' '
         else:
             return ''   


 def getCode(n, delta, state):
     if n == delta:
         return getSym(False, state)               
     elif n >= delta * 3:
         s = getSym(True, state)
         if s == ' ' and n > delta * 3:
             return ' | '
         else:           
             return s
     else:
         return getSym(False, state)               
    

 def decodeBits(bits):   
     bits = bits[leadingZeros(bits):][::-1]
     bits = bits[leadingZeros(bits):][::-1]   
     delta = findMin(bits, '1')
     min_zero = findMin(bits, '0')
     if min_zero > 0:
         delta = min(delta, min_zero)   
     state = '1'
     n = 0
     res = ""
     for b in bits:
         if b != state:           
             res += getCode(n, delta, state)
             state = b
             n = 0
         n+=1
                      
     return res + getCode(n, delta, state)
    
 def decodeMorse(morseCode):
     MORSE_CODE['|'] = ' '   
     return ''.join([MORSE_CODE[x] for x in morseCode.split(' ')])
