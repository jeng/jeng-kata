 import java.util.GregorianCalendar;
 import java.util.Date;

 public class Kata {
   public static int unluckyDays(int year) {

     int result = 0;
    
     GregorianCalendar c = new GregorianCalendar();   
     c.setGregorianChange(new Date(Long.MIN_VALUE));

     c.set(GregorianCalendar.YEAR, year);
     c.set(GregorianCalendar.DAY_OF_MONTH, 13);
    
     for(int i = 0; i < 12; i++){
       c.set(GregorianCalendar.MONTH, i);
      
       if (c.get(GregorianCalendar.DAY_OF_WEEK) == GregorianCalendar.FRIDAY){     
         result++;
       }                 
     }
        
     return result;
   }
 }
