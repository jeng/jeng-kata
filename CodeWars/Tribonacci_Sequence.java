 import java.util.Vector;
 import java.util.List;

 public class Xbonacci {
   final int SEED_SZ = 3;
  
   double sumLastX(List<Double> s){
     int ln = s.size() - 1;
     double d =0;
     for(int i = ln; i > ln-SEED_SZ; i--)
       d += s.get(i);
     return d;
   }
  
   double[] f(List<Double> x){
     double[] d = new double[x.size()];
     for(int i = 0; i < x.size(); i++)
       d[i] = x.get(i);   
     return d;
   }
    
   Vector<Double> g(double[] a){
     Vector<Double> r = new Vector<Double>();
     for(double d : a)
       r.add(new Double(d));
     return r;     
   }
    
   public double[] tribonacci(double[] s, int n) {
     Vector<Double> ld = g(s);
     if (n <= 0)
       return new double[0];
    
     if (n <= SEED_SZ)
       return f(ld.subList(0, n));
    
     for(int i = 0; i < n - SEED_SZ; i++)
       ld.add(sumLastX(ld));

     return f(ld);
   }
 }