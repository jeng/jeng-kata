 function countDivBy(ints, denom){
   return ints.reduce(
     function(a, b) {      
       c = (b % denom == 0) ? 1 : 0     
       return a + c;
     }, 0);
 }

 function isOdd(ints){
   var e = countDivBy(ints, 2);
   var o = ints.length - e;
   return o > e;
 }

 function findOutlier(integers){
   var f;
   if (isOdd(integers))
     f = function(x){return x % 2 == 0;}
   else
     f = function(x){return x % 2 != 0;}
   return integers.filter(f)[0]; 
 }
