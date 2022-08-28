 import java.util.Vector;
 import java.util.List;

 public class Xbonacci {

   double sumLastX(List<Double> s, int x){
     int ln = s.size() - 1;
     double d =0;
     for(int i = ln; i > ln-x; i--)
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
    
   public double[] xbonacci(double[] s, int n) {
     Vector<Double> ld = g(s);
     int seed_sz = s.length;
    
     if (n <= 0)
       return new double[0];
    
     if (n <= seed_sz)
       return f(ld.subList(0, n));
    
     for(int i = 0; i < n - seed_sz; i++)
       ld.add(sumLastX(ld, seed_sz));

     return f(ld);
   }
 }
