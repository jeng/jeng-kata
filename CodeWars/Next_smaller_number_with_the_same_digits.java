 import java.util.Arrays;
 import java.util.Collections;

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
    
     public static long nextSmaller(long n)
     {
       String s = Long.toString(n);
      
       for(int i = s.length() - 1; i >= 0; i--){
         String working = s.substring(i, s.length());
         String backward = sortString(working, SortDirection.Backward);           
         String forward = sortString(working, SortDirection.Forward);       
         String prefix = s.substring(0, i);
         long currentMin = Long.parseLong(prefix + forward);
         char currentDigit = s.charAt(i);
        
         if (currentMin < n){         
           int index = 0;
           for(int j = 0; j < backward.length() -1 && backward.charAt(j) >= currentDigit ; j++)
              index++;
             
           if (prefix.length() == 0 && backward.charAt(index) == '0')
             continue;                     
           
            return Long.parseLong(
             prefix +
             backward.charAt(index) +           
             backward.substring(0, index) +
             backward.substring(index + 1));
         }           
       }
       return -1;
     }
 }
