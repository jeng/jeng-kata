 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function shuffleMerge(first, second) {
  
   if (first === null)
     return second;
  
   if (second === null)
     return first;
    
   var w1 = first;
   var w2 = second;
  
   var res = new Node(w1.data);
   var rhead = res;
   res.next = new Node(w2.data);
   res = res.next;
  
   w1 = w1.next;
   w2 = w2.next;

   while(w1 !== null || w2 !== null){
    
     if (w1 !== null) {
       res.next = new Node(w1.data);
       res = res.next;
       w1 = w1.next;
     }
    
     if (w2 !== null) {
       res.next = new Node(w2.data);
       res = res.next;
       w2 = w2.next;   
     }       
   }
  
   return rhead;
 }
