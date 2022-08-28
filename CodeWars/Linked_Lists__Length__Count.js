 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function walk(head, lambda){
   var w = head;
   while(w !== null){
     lambda(w);
     w = w.next;
   }   
 }


 function length(head) {
   var c = 0;
   walk(head, function(x){ c++; });
   return c;
 }

 function count(head, data) {
   var c = 0;
   walk(head, function(n){
     if (n.data === data)
       c++;
   });     
   return c; 
 }
