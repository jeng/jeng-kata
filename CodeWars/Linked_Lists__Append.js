 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function tail(list){
   var w = list;
  
   if (w === null)
     return w;
    
   while(w.next !== null)
     w = w.next;
    
   return w;   
 }

 function append(listA, listB) {
   if (listA === null && listB === null)
     return null;
   else if (listA === null)
     return listB;
   else if (listB === null)
     return listA;
    
   var t = tail(listA);
   t.next = listB;
   return listA;
 }
