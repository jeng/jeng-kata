 #include <cmath>
 class StepInPrimes
 {
 private:
   static bool isPrime(int num)
   {
     int i = 1;
     while(++i <= sqrt(num))
       if (num%i == 0)
         return false;
     return true;
   }
  
 public:
     // if there are no such primes return {0, 0}
     static std::pair <long long, long long> step(int g, long long m, long long n)
     {
       for(int i = m; i<= n; i++)
       {
         if (isPrime(i))
         {
           int stepcount = 1;
           int j = i - 1;
           while(stepcount <= g && j >= m)
           {
             if (isPrime(j) && g == stepcount)
               return {j, i};
             stepcount++;
             j--;
           }
         }
       }
       return {0,0};
     }
 };

     * 6 years ago
     * Refactor
     * Discuss

        Python:

 import math
 def is_prime(num):
     i = 2
     while i <= math.sqrt(num):
         if num % i == 0:
             return False
         i = i + 1
     return True


 def step(g, m, n):
     i = m
     while i <= n:
         if is_prime(i):
             stepcount = 1
             j = i-1
             while stepcount <= g and j >= m:
                 if is_prime(j) and g == stepcount:
                     return [j, i]
                 stepcount = stepcount + 1                   
                 j = j - 1               
         i = i + 1
     return None       
