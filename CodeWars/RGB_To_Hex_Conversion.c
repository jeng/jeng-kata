 #include <stdio.h>

 int rngchk(int x){
   if (x < 0)
     return 0;
   if (x > 255)
     return 255;
   else
     return x;
 }

 int rgb(int r, int g, int b, char *output)
 {
    //pass the result to the 'char *output'
    unsigned int color;
    color = rngchk(r) << 16;
    color = color | rngchk(g) << 8;
    color = color | rngchk(b);
    sprintf(output, "%.6X", color);  
    return 0;
 }
