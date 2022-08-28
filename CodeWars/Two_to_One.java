
 public class TwoToOne {
     static class Node{
       char value;
       Node left;
       Node right;
       Node(char c){
         this.value = c;
         this.left = null;
         this.right = null;
       }
     }

     private static void insert(Node tree, char c){
       if (tree == null)
         return;
        
       if (tree.value == c)
         return;
      
       if (c < tree.value){
         if (tree.left == null){
           tree.left = new Node(c);
           return;
         }
         else {
           insert(tree.left, c);
         }
       }
      
       if (c > tree.value){
         if (tree.right == null){
           tree.right = new Node(c);
           return;
         }
         else {
           insert(tree.right, c);
         }
       }     
     }

     private static String walk(Node tree){
       if (tree == null){
         return "";
       }
       else {
         String s = walk(tree.left);
         s += tree.value;
         s += walk(tree.right);
         return s;
       }
     }

     private static Node buildTree(Node tree, String s){
       for(int i = 0; i < s.length(); i++){
         if (tree == null){
           tree = new Node(s.charAt(i));
         }
         else{
           insert(tree, s.charAt(i));
         } 
       }
       return tree;
     }

     public static String longest (String s1, String s2) {
         Node tree = null;
         tree = buildTree(tree, s1);
         tree = buildTree(tree, s2);       
         return walk(tree);
     }
 }