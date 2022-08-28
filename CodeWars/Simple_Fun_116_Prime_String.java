 public class Kata {
    
     public static boolean chunksMatch(String s, int chunkSize){     
       String last = "";
       for(int i = 0; i < s.length(); i+=chunkSize){
         String sub = s.substring(i, Math.min(i+chunkSize, s.length()));       
         if (i > 0 && !last.equals(sub)){
           return false;         
         }
         last = sub;
       }
       return true;
     }
    
     public static boolean primeString(String s) {     
       for(int i = s.length()/2; i >= 1; i--){
         if (chunksMatch(s, i)){
           return false;
         }         
       }
       return true;
     }
 }
