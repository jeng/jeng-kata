 function removeLeadingZeros(a){ 
   var res = "";
   var skip = true;
   for(var i = 0; i < a.length; i++){
     if (a[i] == '0' && skip)
       continue;
      
     skip = false;
     res += a[i];
   }
   return res;
 }

 function sumStrings(a,b) {
   var la = a.length;
   var lb = b.length;
   var m = Math.max(la--, lb--);
   var c = 0;
   var res = "";
  
   for(var i = 0; i < m; i++){
     var ad = 0;
     var bd = 0;
    
     if (la >= 0){
       ad = parseInt(a[la--]);
     }
    
     if (lb >= 0){
       bd = parseInt(b[lb--]);
     }
    
     var nb = ad + bd + c;
     c = Math.floor(nb/10);
     var d = nb % 10;
     res = d.toString() + res;
   }
  
   if (c == 1){
     res = '1' + res;
   }
  
   return removeLeadingZeros(res);
 }
