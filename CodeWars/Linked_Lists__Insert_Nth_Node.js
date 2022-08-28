 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function insertNth(head, index, data) {
   var n = new Node(data);
   var prev = null;
   var w = head;
  
   if (w === null && index === 0){
     return n;
   }
   else{
  
     while(w !== null && index-- > 0){
       prev = w;
       w = w.next;
     }
        
     if (w === null && index > 0){
       throw "Invalid Argument";
     }
    
     n.next = w;
    
     if (prev === null)
       return n;
     else     
       prev.next = n;         
   }
  
   return head;
 }
