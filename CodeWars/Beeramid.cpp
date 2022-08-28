 int beeramid(int bonus, double price)
 {
   int howManyBeers = bonus/price;
   int sum = 0;
   int row = 1;
   while(howManyBeers > 0){
     int cansUsed = row * row++;   
     howManyBeers -= cansUsed;
     if (howManyBeers >= 0)
       sum++;   
   } 
   return sum;
 }
