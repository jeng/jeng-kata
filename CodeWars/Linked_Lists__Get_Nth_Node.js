 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function getNth(node, index) {
   var w = node;
  
   while(w !== null && index-- > 0)
     w = w.next;
    
   if (w === null)
     throw "Invalid argument";
  
   return w;
 }
