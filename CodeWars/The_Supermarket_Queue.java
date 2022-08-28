 import java.util.Arrays;
 public class Solution {

     static int smallestIndex(int[] queues){
       int min = Integer.MAX_VALUE;
       int idx = 0;
       for (int i= 0; i < queues.length; i++){
         if (queues[i] < min){
           min = queues[i];
           idx = i;
         }
       }
       return idx;
     }

     public static int solveSuperMarketQueue(int[] customers, int n) {
       int[] queues = new int[n];
       for(int i = 0; i < customers.length; i++){
         int idx = smallestIndex(queues);
         queues[idx] += customers[i];
       }
       int max = 0;
       for(int i = 0; i < queues.length; i++){
         if (queues[i] > max)
           max = queues[i];
       }
       return max;
     }
    
 }
