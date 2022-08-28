 import java.util.Stack;

 public class Kata
 {
     public static String expandedForm(int num)
     {
       Stack<Integer> stack = new Stack<Integer>();
       int m = 1;
      
       for (int i = 0; num > 0; i++){
         int n = num % 10;
         num = num / 10;
         if (n != 0)
           stack.push(m * n);
         m *= 10;
       }

       String s = "";
       while(!stack.empty()){
         if (s != "")
           s += " + ";       
         s += String.valueOf(stack.pop());
       }
      
       return s;
     }
 }
