 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function sortedMerge(first, second) {

   if (first === null)
     return second;
  
   if (second === null)
     return first;
    
   var w1 = first;
   var w2 = second;
  
   var res = null;
   if (w1.data < w2.data){
     res = new Node(w1.data);
     w1 = w1.next;
   }   
   else {
     res = new Node(w2.data);
     w2 = w2.next;
   }
   var rhead = res;

   while(w1 !== null || w2 !== null){
     if (w1 === null){
       res.next = new Node(w2.data);
       w2 = w2.next;
     }
     else if (w2 === null){
       res.next = new Node(w1.data);
       w1 = w1.next;
     }     
     else if (w1.data < w2.data){
       res.next = new Node(w1.data);
       w1 = w1.next;
     }   
     else {
       res.next = new Node(w2.data);
       w2 = w2.next;
     }
     res = res.next;
   }
  
   return rhead;
 }
