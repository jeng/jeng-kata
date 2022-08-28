 using namespace std;
 class Bouncingball
 {
 public:
     static int bouncingBall(double h, double bounce, double window)
     {
       int n = 0; double i = h;
       if (h <= 0) return -1;
       if (bounce < 0 || 1 <= bounce) return -1;
       if (window >= h) return -1;
       while(i >= window)
       {
         n++;
         i *= bounce;
         if (i >= window)
           n++;
       }
       return n;
     }
 };
