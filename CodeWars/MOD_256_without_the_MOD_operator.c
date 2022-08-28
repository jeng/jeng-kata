 int mod256WithoutMod(int n)
 {
   int s = (n < 0) ? -1 : 1;
   int r = ((n * s) ^ 0x100) & 0xff;
   return r * s;
 }
