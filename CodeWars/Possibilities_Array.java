 import java.util.SortedSet;
 import java.util.TreeSet;
 import java.util.Arrays;
 import java.util.stream.Collectors;

 public class Solution {

   public static boolean isAllPossibilities(int[] arg) {
     SortedSet<Integer> s = new TreeSet<Integer>(Arrays.stream(arg).boxed().collect(Collectors.toList()));
     return s.size() > 0 && s.size() == arg.length && s.first() == 0 && s.last() == arg.length-1;
   }

 }
