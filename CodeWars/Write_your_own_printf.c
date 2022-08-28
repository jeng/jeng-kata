 #include <stdarg.h>
 #include <stdlib.h>
 #include <stdarg.h>

 int my_len(const char *s) {
   int n = 0;
   while (*(s++) != 0)n++;
   return n;
 }

 char *int_to_str(int n) {
   char s[11];
   char *result;
   int neg = 0;
   int i = 0, j;

   if (n < 0) {
     neg = 1;
     n *= -1;
   }

   do {
     int m = n % 10;
     n = n / 10;
     m = m + '0';
     s[i++] = m;
   } while (n != 0);

   if (neg) {
     result = (char *)calloc(i + 2, sizeof(char));
     result[0] = '-';
     j = 1;
   }
   else {
     result = (char *)calloc(i + 1, sizeof(char));  
     j = 0;
   }

   for (; i > 0; j++) {
     result[j] = s[--i];
   }

   return result;
 }

 char *mr_asprintf(const char *format, ...)
 {
   va_list ap;
   int i, q = 0, pon = 0; 
   int ssize = my_len(format) + 1;
   char *result = (char *)malloc(ssize * sizeof(char));
   char type;

   va_start(ap, format);
   for (i = 0; i < my_len(format); i++) {
     if (format[i] == '{' && pon) {
       result[q++] = '{';
       pon = 0;
     }
     else if (format[i] == '{') {
       pon = 1;
     }
     else if (format[i] == '}' && !pon) {
       result[q++] = format[i];
     }
     else if (format[i] == '}' && pon) {
       pon = 0;
       if (type == 's') {
         char *s = va_arg(ap, char*);
         int k = 0;
         ssize += my_len(s) + 1;
         result = (char *)realloc(result, ssize * sizeof(char));
         for (k = 0; k < my_len(s); k++) {
           result[q++] = s[k];
         }
       }
       else if (type == 'i') {
         int n = va_arg(ap, int);
         char *s = int_to_str(n);
         int k = 0;
         ssize += my_len(s) + 1;
         result = (char *)realloc(result, ssize * sizeof(char));
         for (k = 0; k < my_len(s); k++) {
           result[q++] = s[k];
         }
         free(s);
       }
     }
     else if (pon) {
       type = format[i];
     }
     else {
       pon = 0;     
       result[q++] = format[i];
     }
   }

   va_end(ap);

   result[q] = '\0';
   return result;
 }
