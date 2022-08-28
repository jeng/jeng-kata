 import java.util.stream.IntStream;
 import java.util.Arrays;

 public class Primes {
   public static IntStream stream() {
     int MAX = 32452843;
     int [] tbl = new int[MAX]; 
     tbl[0] = -1; tbl[1] = -1; tbl[2] = 2;
            
     for(int i = 2; i < MAX; i++){   
       if (tbl[i] == -1)
         continue;
      
       tbl[i] = i;
            
       for(int j = i+i; j < MAX; j+=i){       
         tbl[j] = -1;         
       }
     }

     return Arrays.stream(tbl).filter(x -> x != -1);
   }
 }