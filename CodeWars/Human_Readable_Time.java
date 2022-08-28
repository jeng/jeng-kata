 public class HumanReadableTime {
   public static String makeReadable(int seconds) {
     int ss = seconds % 60;
     seconds = seconds / 60;
     int mm = seconds % 60;
     seconds = seconds / 60;
     return String.format("%02d:%02d:%02d", seconds, mm, ss);
   }
 }
