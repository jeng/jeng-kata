 function Node(data) {
   this.data = data;
   this.next = null;
 }

 function push(head, data) {
   var n = new Node(data);
   n.next = head;
   return n;
 }

 function buildOneTwoThree() {
   return push(push(push(null, 3), 2), 1);
 }
