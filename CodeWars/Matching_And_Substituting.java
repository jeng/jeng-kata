 import java.util.regex.Pattern;

 public class MatchSubst {
   public static class Info{
       public String author;
       public String program;
       public String original_program;
       public String phone;
       public String date;
       public String original_version;
       public String version;
       public String level;
       public String corporation;
       @Override
       public String toString() {       
         if (!phone.matches("\\+1-\\d{3}-\\d{3}-\\d{4}") || !original_version.matches("\\d+\\.\\d+")){         
           return "ERROR: VERSION or PHONE";
         }
         String v = (original_version.equals("2.0")) ? "2.0" : version;       
         return "Program: " + program + " Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: " + v;
       }
     }
     public static String change(String s, String prog, String version) {
       String nvPairs[] = s.split("\n");
       Info info = new Info();
       info.program = prog;
       info.version = version;
       for(String nvp : nvPairs){       
         String nv[] = nvp.split(":");
         if (nv.length < 2)
           continue;
         nv[0] = nv[0].strip();
         nv[1] = nv[1].strip();
         if (nv[0].equals("Program title")){
           info.original_program = nv[1];
         }         
         if (nv[0].equals("Author")){
           info.author = nv[1];
         }         
         if (nv[0].equals("Phone")){
           info.phone = nv[1];
         }         
         if (nv[0].equals("Date")){
           info.date = nv[1];
         }         
         if (nv[0].equals("Version")){
           info.original_version = nv[1];
         }         
         if (nv[0].equals("Level")){
           info.level = nv[1];
         }         
         if (nv[0].equals("Corporation")){
           info.corporation = nv[1];
         }                 
       }
       return info.toString();
     }
 }
