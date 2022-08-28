 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function reverse(list) {
   // Your code goes here.
   if (list === null)
     return null;
  
   var w = list;     
   var front = null;

   while(w !== null){
     var n = new Node(w.data);
     n.next = front;
     front = n;
     w = w.next;
   }
  
   list.data = front.data;
   list.next = front.next;
 }
