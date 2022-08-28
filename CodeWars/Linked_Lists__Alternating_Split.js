 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function Context(first, second) {
   this.first = first;
   this.second = second;
 }

 function alternatingSplit(head) {
   var w = head;
   var m = null;
   var n = null;
   var i = 0;
   var mhead = null;
   var nhead = null;
  
   if (w === null)
     throw "Cannot split an empty list";
  
   if (w.next === null)
     throw "Cannot splist a list with a single element";
    
   while(w !== null){
     if ( i % 2 === 0){
       if (m === null){     
         m = w;
         mhead = m;
       }
       else {
         m.next = w;
         m = m.next;       
       }
     }
     else {
       if (n === null) {
         n = w;
         nhead = w;
       }       
       else {
         n.next = w;
         n = n.next;       
       }
     }
     w = w.next;
     i++;
   }
  
   m.next = null; n.next = null;
   return new Context(mhead, nhead);
 }

     * 5 years ago
     * Refactor
     * Discuss
   Draft
   Linked Lists - Move Node In-place

        JavaScript:

 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function moveNode(source, dest) { 
   if (source === null)
     throw "null source"
   else if (dest === null)
     throw "null dest"
   else if (source.data === null)
     throw "empty source node"
   else {
     var tmp = (source.next === null) ? new Node() : source.next;
     if (dest.data === null){     
       dest.data = source.data;
       dest.next = null;     
     }
     else {
       var n = new Node(dest.data);
       n.next = dest.next;
       dest.data = source.data;
       dest.next = n;
     }
     source.data = tmp.data;
     source.next = tmp.next
   }
 }
