 import java.lang.Integer;
 public class DeltaBits {
     public static int convertBits(int a, int b) {     
       return Integer.toBinaryString(a ^ b).replace("0", "").length();
     }
 }
