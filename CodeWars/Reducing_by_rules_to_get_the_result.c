 typedef double (*rulesFnct) (double, double);

 double reduceByRules(double numbers[], int numberCount, rulesFnct rules[], int rulesCount)
 {
   int rc = 0;
   int i = 0;
   double res = numbers[i++];
   for (;i < numberCount; i++){
     res = rules[rc](res, numbers[i]);
     rc = (rc + 1) % rulesCount;
   }
   return res;
 }
