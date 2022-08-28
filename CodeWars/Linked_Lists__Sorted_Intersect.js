 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function sortedIntersect(first, second) {
   var rhead = null;
   var res = null;
   while(first !== null && second !== null){
     if (first.data === second.data){
       var n = first.data;
       if (res === null) {
         res = new Node(n);
         rhead = res;
       }
       else{
         res.next = new Node(n);
         res = res.next;
       }
       while (first != null && first.data === n)
         first = first.next;
       while (second != null && second.data === n)       
         second = second.next;
     }
     else if (first.data < second.data){
       first = first.next;
     }
     else{
       second = second.next;
     }   
   }
   return rhead;
 }
