 #include <stdlib.h>
 #include <string.h>

 typedef struct {
   size_t rows;
   size_t columns;
   size_t width;
   size_t height;
   char *buffer;
 } Environment;

 void insert(Environment *env, char c, int x, int y) {
   env->buffer[(y * env->width) + x] = c;
 }

 void fill(Environment *env, char fillchar, char delimiter, int y) {
   for (int i = 0; i < env->width-1; i++) {
     insert(env, fillchar, i, y);
   }
   for (int i = 0; i < env->columns + 1; i++) {
     insert(env, delimiter, i * 4, y);
   }
   insert(env, '\n', env->width-1, y);
 }

 char* pattern(size_t rows, size_t columns, const char* str_in) { 
   Environment env;
   env.rows = rows;
   env.columns = columns; 
   env.width = (env.columns * 4) + 2;
   env.height = (env.rows * 2) + 1;
   //This gets freed in the unit test so alloc on the heap
   env.buffer = (char*)calloc(env.width * env.height, sizeof(char));

   for (int y = 0; y < (env.rows * 2) + 1; y++) {
     if (y % 2 == 0)
       fill(&env, '-', '+', y);
     else   
       fill(&env, ' ', '|', y);
   }

   int x = 2;
   int y = 1;
   for (int i = 0; i < strlen(str_in) && y < env.height; i++){  
     if (i != 0 && (i % env.columns) == 0){
       y+=2;
       x=2;
     }
     insert(&env, str_in[i], x, y);
     x += 4;
   }

   insert(&env, '\0', env.width-1, env.height-1);

   return(env.buffer);
 }
