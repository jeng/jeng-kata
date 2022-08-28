 public class Kata {

   public static String encrypt(final String text, final int n) {
     if (text == null)
       return text;
      
     String working = text;
     int m = n;
     while(m-- > 0){
       String so = "";
       String se = "";
       for(int i = 0; i < working.length(); i++) {
         if (i % 2 == 0)
           se += working.charAt(i);
         else
           so += working.charAt(i);
       }
       working = so + se;
     }   
     return working;  
   }
  
   public static String decrypt(final String encryptedText, final int n) {
     if (encryptedText == null)
       return encryptedText;
      
     String working = encryptedText;
     int m = n;
     int seLn = working.length() / 2;
     while(m-- > 0){
       String newWorking = "";     
       for(int i = 0, j = seLn; j < working.length(); i++, j++) {
         newWorking += working.charAt(j);
        
         if (i < seLn)
           newWorking += working.charAt(i);
       }
       working = newWorking;
     }   
     return working;     
   } 
 }
