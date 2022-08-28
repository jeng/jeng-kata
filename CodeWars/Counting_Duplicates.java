 public class CountingDuplicates {
  
   static class Node{
     int count;
     char value;
     Node left;
     Node right;
    
     Node(char v){
       count = 0;
       left = null;
       right = null;
       value = v;
     }
   }
  
   private static void insert(Node tree, char c){
     if (tree == null)
       return;
  
     if (tree.value == '?'){
       tree.value = c;
       return;
     }

     if (tree.value == c){
       tree.count++;
       return;
     }
    
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
  
   static int collect(Node tree){
     int n = 0;
    
     if (tree == null)
       return n;
    
     n += collect(tree.left);
     if (tree.count > 1)
       n++;
     n += collect(tree.right);
    
     return n;
   }
   
   public static int duplicateCount(String text) {
     String s = "i9420137568ecabdgfhrnljkmpoqwustvyxz";
     Node t = new Node('?');
    
     for(int i = 0; i < s.length(); i++){
       insert(t, s.charAt(i));
     }
   
    for(int i = 0; i < text.length(); i++){
       insert(t, Character.toLowerCase(text.charAt(i)));
     }
   
    return collect(t);
   }
 }
