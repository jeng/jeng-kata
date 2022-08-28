 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function reduce(source, lambda, init){
   if (source === null || source.data === null)
     return init;
   else
     return reduce(source.next, lambda, lambda(init, source.next));
 }

 function count(source){
   return reduce(source, function(a, b){ return a + 1; }, 0);
 }

 function frontBackSplit(source, front, back) {
   var c = count(source);
   if (source === null || front === null || back === null || c < 2){
     throw "Invalid Arguments";
   }
   var lc1 = Math.ceil(c/2);
   var w = source;
   var p = source; 
   front.data = w.data;
   front.next = w.next;   
  
   while(w !== null){   
     if (lc1-- == 0) {
       back.data = w.data;
       back.next = w.next;
       p.next = null;
       if (c == 2)
         front.next = null;
       return;
     }
     p = w;
     w = w.next;
   }
 }
