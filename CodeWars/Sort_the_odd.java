 import java.util.Vector;
 import java.util.Collections;

 public class Kata {
  
   static boolean isOdd(int n){
     return (n % 2 == 1);
   }
  
   static Vector<Integer> collectOdd(int[] array){
     Vector<Integer> v = new Vector<Integer>();
     for(int i = 0; i < array.length; i++){
       if (isOdd(array[i]))
         v.add(array[i]);
     }
     Collections.sort(v);
     return v;
   }

   public static int[] sortArray(int[] array) {
     Vector<Integer> odds = collectOdd(array);
     for(int i = 0, j = 0; i < array.length; i++){
       if (isOdd(array[i]))
         array[i] = odds.elementAt(j++);
     } 
     return array;
   }
 }
