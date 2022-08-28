 #include <cmath>
 #include <algorithm>
 #include <iomanip>
 class Suite
 {
 private:
   // We are taking the log of 1!+2!+3!+...+n!
   // log of factorial can be computed by doing
   // log(1) + log(2) + ... + log(n)
   // since log(n!) = log(1*2*...*n) = log(1) + log(2) + ... + log(n)
   //
   // to avoid overflow we need to use log(sum factorial/factorial) =
   // log(sum factorial) - log(factorial)
   //
   // The sum can be thought of as log(e^log(1!) + e^log(2!) + ... + e^log(n!))
   //
   // A trick can be used to compute the log-sum-exp
   //       n
   //       --
   // a+log \  exp{xn - a}
   //       /
   //       --
   //       n=1
   //
   // where a = max(xn)
  
   static double logSumExp(int n)
   {
     //Collect all of the factorial logs
     std::vector<double> facs(0);
     for(int i = 1; i <= n; i++)
       facs.push_back(logFactorial(i));
      
     //find the max
     double a = *std::max_element(facs.begin(), facs.end());
    
     //sum
     double r = 0;
     for(double x : facs)
       r += exp(x-a);
    
     return a + log(r);
   }
  
   static double logFactorial(int n)
   {
     double r = log(n);
     while(--n > 0)
       r += log(n);
     return r;
   }
  
   static double factorial(int n)
   {
     double r = n;
     while(--n > 0)
       r*= n;
     return r;
   }
  
   static double sumFactorial(int n)
   {
     double r = 0;
     for(int i = 1; i <= n; i++)
       r+=factorial(i);
     return r;
   }

  
 public:
   static double going(int n)
   {
     double d;
     if (n > 10)
     {
       d = logSumExp(n)-logFactorial(n);
       d = exp(d);
     }
     else
     {
       d = sumFactorial(n)/factorial(n);
     }
     return floor(d * pow(10,6)) / pow(10,6);
   }
 };
