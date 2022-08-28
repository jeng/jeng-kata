 import java.util.Arrays;
 import java.util.List;
 import java.util.stream.Collectors;
 import java.util.regex.Matcher;
 import java.util.regex.Pattern;
 import java.util.TreeSet;
 import java.util.Comparator;
 import java.lang.String;

 class CompareID implements Comparator<String>{
   public Integer id(String word){   
     Matcher matcher = Pattern.compile(".*(\\d).*").matcher(word);
     if (matcher.find()){     
       return new Integer(matcher.group(1));
     }
     return 0;   
   }
  
   public int compare(String word1, String word2){
     Integer n = id(word1);
     Integer m = id(word2);
     return n.compareTo(m);
   }     
 }

 public class Order {    
   public static String order(String words) {
     String wordList[] = words.split(" ");
     TreeSet<String> result = new TreeSet<String>(new CompareID());
     Arrays.stream(wordList).forEach(w -> result.add(w)); //whatever java
     return String.join(" ", result);
   }
 }
