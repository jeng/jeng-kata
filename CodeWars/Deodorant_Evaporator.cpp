 using namespace std;
 class Evaporator
 {

   public:
   static int evaporator(double content, double evap_per_day, double threshold)
   {
     double x, e = evap_per_day /100.0;
     int d;
     for(d = 0, x = 100; x > threshold; x-=(x*e), d++);
     return d;
   }
 };
