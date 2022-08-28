 function sumstring(s){
   var x = 0;
   for(var i = 0; i < s.length; i++){
     x += parseInt(s[i]);
   }
   return x;
 }
 function orderWeight(s) {
   var a = s.split(" ");
   a.sort(function(a, b){
     var x = sumstring(a);
     var y = sumstring(b);   
     if (x === y){
       if (a < b) return -1;
       if (a === b) return 0;
       if (a > b) return 1;     
     }
     else {
       if (x < y) return -1;
       if (x === y) return 0;
       if (x > y) return 1;     
     }
   });
   var res = "";
   for(var i = 0; i < a.length; i++){
     res += (((res === "") ? "" : " ") + a[i].toString());
   }
   return res;
 }
