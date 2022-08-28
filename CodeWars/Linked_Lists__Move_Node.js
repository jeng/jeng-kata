 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function Context(source, dest) {
   this.source = source;
   this.dest = dest;
 }

 function moveNode(source, dest){
   d = source;
   if (d == null)
     throw "Empty source";
   source = d.next;
   d.next = dest;
   dest = d;
   return new Context(source, dest);
 }
