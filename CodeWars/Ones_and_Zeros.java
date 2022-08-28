 import java.util.List;

 public class BinaryArrayToNumber {
     public static int ConvertBinaryArrayToInt(List<Integer> b) {
       if (b.size() == 0) return 0;
       Integer i = b.remove(0);
       if (b.size() == 0) return i;     
       return (i << b.size()) | ConvertBinaryArrayToInt(b);
     }
 }
