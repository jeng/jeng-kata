 import java.lang.Exception;
 import java.util.Hashtable;
 import java.util.Vector;
 import java.lang.String;

 public class Catalog {

   static public class ParseBlock{
     public String rest;
     public String token;
     public ParseBlock(String token, String rest){
       this.token = token;
       this.rest = rest;
     }
   }

   static public class Product {
     private ParseBlock tag(String s) throws Exception {
       if (s.length() <= 0){
         throw new Exception("Invalid string length");
       }
       if (s.charAt(0) != '<'){
         throw new Exception("Tag error got " + s.charAt(0));
       }
       for(int i = 1; i < s.length(); i++){
         if (s.charAt(i) == '>'){
           return new ParseBlock(s.substring(0, i+1), s.substring(i + 1, s.length()));
         }
       }
       throw new Exception("Invaid tag no gt or lt found");
     }
    
     private ParseBlock value(String s) throws Exception{
       if (s.length() <= 0){
         throw new Exception("Invalid string length value");
       }
       if (s.charAt(0) == '<' || s.charAt(0) == '>'){
         throw new Exception("Invalid value");
       }
       for(int i = 0; i < s.length(); i++){
         if (s.charAt(i) == '<'){
           return new ParseBlock(s.substring(0, i), s.substring(i, s.length()));
         }
       }
       throw new Exception("Invaid Value no tag found");
     }
    
     public String name;
     public String prx;
     public String qty;
    
     private void parse_line(String prodline) throws Exception{
       ParseBlock pb = tag(prodline);
       assert(pb.token.equals("<prod>"));
       while(!pb.token.equals("</prod>")){       
         pb = tag(pb.rest);       
         if (pb.token.equals("<name>")){         
           pb = value(pb.rest);
           this.name = pb.token;
           pb = tag(pb.rest);
           assert(pb.token.equals("</name>"));
         }
         else if (pb.token.equals("<prx>")){
           pb = value(pb.rest);
           this.prx = pb.token;
           pb = tag(pb.rest);
           assert(pb.token.equals("</prx>"));
         }
         else if (pb.token.equals("<qty>")){
           pb = value(pb.rest);
           this.qty = pb.token;
           pb = tag(pb.rest);
           assert(pb.token.equals("</qty>"));
         }       
       }
     }
    
     public Product(String prodline) throws Exception{
       parse_line(prodline);     
     }
   }
  
   public static String catalog(String s, String article){   

     String result = "";
     try{
       String[] data = s.split("\n", 0);
       for(int i = 0; i < data.length; i++){
         String pline = data[i].trim();
         if (pline.length() > 0){
           Product p = new Product(pline);
           if(p.name.indexOf(article) >= 0){
             if (result != "")
               result += "\n";
             result += p.name + " > prx: $" + p.prx + " qty: " + p.qty;
           }
         }
       }           
     }catch(Exception e){
       System.out.println(e);
     }
     return result.length() == 0 ? "Nothing" : result;    
   }
 }
