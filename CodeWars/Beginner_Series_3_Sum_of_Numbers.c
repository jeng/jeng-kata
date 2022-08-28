 int get_sum(int a , int b) {
     int c = (a < b) ? a : b;
     int d = (a > b) ? a : b;
     int e = c;   
     for(int i = c + 1; i <= d; i++)
       e += i;
     return e;
 }
