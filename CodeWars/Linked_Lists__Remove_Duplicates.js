 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function contains(head, n){
   if (head === null)
     return false;
    
   var w = head;
   while(w !== null){
     if (w.data === n)
       return true;
     w = w.next;     
   }
   return false;
 }

 function removeDuplicates(head) {
   var w = head;
   var ls = null;
   var res = null;
  
   while(w !== null){
     if (!contains(ls, w.data)){
       if (ls === null){
         res = new Node(w.data);
         ls = res;
       }
       else {
         var n = new Node(w.data);
         ls.next = n;
         ls = n;
       }     
     }
     w = w.next;     
   }
   return res;
 }
