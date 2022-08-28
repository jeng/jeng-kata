 #include <stdlib.h>
 #include <stddef.h>

 int* matrix_addition(size_t n, int matrix_a[n][n], int matrix_b[n][n]) {

 int *result = malloc((n * n) * sizeof(int));

 for(int i = 0; i < n; i++)
   for(int j =0; j < n; j++)
     result[(i * n) + j] = matrix_a[i][j] + matrix_b[i][j];
    
 return result;

 }
