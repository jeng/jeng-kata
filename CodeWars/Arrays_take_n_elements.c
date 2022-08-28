 #include <stddef.h> /* NULL */

 int *ary_take(const int *ary, size_t ary_size, size_t n, size_t *res_size)
 {
     int *new_ary;   
     *res_size = 0;
    
     if (n == 0){
       return NULL;
     }
     else if (n > ary_size){
       *res_size = ary_size;
     }
     else{
       *res_size = n;
     }
    
     new_ary = malloc(sizeof(int) * *res_size);
     memcpy(new_ary, ary, sizeof(int) * *res_size);
     return new_ary;
 }
