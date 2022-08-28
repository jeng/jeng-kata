 #include <inttypes.h>

 void uint32_to_ip(uint32_t ip, char *output)
 { 
   short first = ip & 0xff;
   ip = ip >> 8;
   short second = ip & 0xff;
   ip = ip >> 8;
   short third = ip & 0xff;
   ip = ip >> 8;
   short forth = ip & 0xff;
   sprintf(output, "%d.%d.%d.%d", forth, third, second, first);
  
 }
