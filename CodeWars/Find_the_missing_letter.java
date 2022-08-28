 public class Kata
 {
   public static char findMissingLetter(char[] array)
   {
     char old = array[0];
     for(int i = 1; i < array.length; i++){
       if ((int)array[i] != (int)(old + 1))             
         return (char)(old + 1);     
       old = array[i];
     }
     return (char)(old + 1);
   }
 }
