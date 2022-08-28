 function Node(data) {
   this.data = data === undefined ? null : data;
   this.next = null;
 }

 function mergeSort(list) {
   if (list == null)
     return null;
   else if (list.next === null)
     return list;
   else {
     var f = new Node();
     var b = new Node(); 
     frontBackSplit(list, f, b);
     return sortedMerge(mergeSort(f), mergeSort(b));
   }
 }
