 char* toLeetSpeak (char *s)
 {
   int ln = strlen(s), i=0;
   char *u = "@8(D3F6#!JK1MN0PQR$7UVWXY2";
   char *r = calloc(ln + 1, sizeof(char));
   for(i = 0; i < ln; i++) {
     int x = s[i] - 'A';
     r[i] = (0 <= x && x < 26) ? u[x] : s[i];
   }
   return r;    
 }
