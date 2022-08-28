 import java.util.Arrays;
 import java.util.Collections;
 import java.lang.Character;

 public class Kata
 { 
     static enum SortDirection {Backward, Forward};
    
     public static String sortString(String s, SortDirection d){
       char charArr[] = s.toCharArray();
       if (d == SortDirection.Backward){
         Character [] rev = new Character[charArr.length];
         for(int i = 0; i < charArr.length; i++){
           rev[i] = charArr[i];
         }
         Arrays.sort(rev, Collections.reverseOrder());   
         for(int j = 0; j < charArr.length; j++){
           charArr[j] = rev[j];
         }
       }
       else {
         Arrays.sort(charArr);
       }
       return new String(charArr);       
     }
    
     public static long nextBiggerNumber(long n)
     {
       String s = Long.toString(n);
      
       for(int i = s.length() - 1; i >= 0; i--){
         String working = s.substring(i, s.length());
         String backward = sortString(working, SortDirection.Backward);           
         String forward = sortString(working, SortDirection.Forward);       
         String prefix = s.substring(0, i);
         long currentMax = Long.parseLong(prefix + backward);
         char currentDigit = s.charAt(i);
        
         if (currentMax > n){         
           int index = 0;
           for(int j = 0; j < forward.length() -1 && forward.charAt(j) <= currentDigit ; j++)
              index++;
           
            return Long.parseLong(
             prefix +
             forward.charAt(index) +           
             forward.substring(0, index) +
             forward.substring(index + 1));
         }           
       }
       return -1;
     }
 }
