 import java.util.Arrays;
 import java.util.Hashtable;

 public class EnoughIsEnough {

   public static int[] deleteNth(int[] elements, int maxOcurrences) {
     Hashtable<Integer, Integer> lookup = new Hashtable<Integer, Integer>();
     int [] result = new int[elements.length];
     int j = 0;
    
     for(int i = 0; i < elements.length; i++){
       int k = elements[i];
       int v = 0;
      
       if (lookup.containsKey(k))
         v = lookup.get(k);
      
       if (v < maxOcurrences){
         result[j++] = k;
         lookup.put(k, v+1);
       }   
     }
    
     return Arrays.copyOf(result,j);
   }
 }
