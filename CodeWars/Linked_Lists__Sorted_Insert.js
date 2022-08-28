 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function sortedInsert(head, data) {
   var w = head;
   var p = null;
  
   while(w !== null && w.data < data){
     p = w;
     w = w.next;
   }
  
   if (head === null)
     return new Node(data);
   else if (p === null) {
     var n = new Node(data);
     n.next = w;
     return n;
   }
   else {
     p.next = new Node(data);
     p.next.next = w;
     return head;
   } 
 }
