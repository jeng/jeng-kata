 import java.util.Arrays;

 public class FindOdd {
   public static int findIt(int[] A) {   
     int o = 0, n = 0;
     Arrays.sort(A);
     for(int x : A){
       if (n == 0){
         o = x;
         n = 1;
       }
       else if(o != x){
         if (n % 2 == 1)
           return o;
         n = 1;
         o = x;
       }
       else {
         n++;
       }
     }
     if (n%2 == 1)
       return o;
     else
       return -1;
   }
 }
