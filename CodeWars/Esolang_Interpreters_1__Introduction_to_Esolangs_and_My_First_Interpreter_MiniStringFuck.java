 public class MyFirstInterpreter {
   private char cell;
   private String code;
   public MyFirstInterpreter(String code) {
     this.cell = 0;
     this.code = code;
   }
   public String interpret() {
     String res = "";
     for(int i = 0; i < code.length(); i++){
       switch(code.charAt(i)){
         case '+': cell = (char)((cell + 1) % 256); break;
         case '.': res += cell; break;
       }
     }     
     return res;
   }
 }
