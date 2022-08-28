 #include <stdio.h>
 #include <stdlib.h>

 enum{
   GRID_SZ = 4,
 };

 int visible_top(int puzzle[GRID_SZ][GRID_SZ], int j){
   int n = 0, i;
   int max = 0;

   if (puzzle[0][j] == 0)
     return n;

   for(i = 0; i < GRID_SZ; i++){
     if (puzzle[i][j] > max) {
       max = puzzle[i][j];
       n++;
     }
   }

   return n;
 }

 int visible_bottom(int puzzle[GRID_SZ][GRID_SZ], int j){
   int n = 0, i;
   int max = 0;

   if (puzzle[GRID_SZ-1][j] == 0)
     return n;

   for(i = GRID_SZ-1; i >= 0; i--){
     if (puzzle[i][j] > max) {
       max = puzzle[i][j];
       n++;
     }
   }

   return n;
 }

 int visible_left(int puzzle[GRID_SZ][GRID_SZ], int i){
   int n = 0, j;
   int max = 0;

   if (puzzle[i][0] == 0)
     return n;

   for(j = 0; j < GRID_SZ; j++){
     if (puzzle[i][j] > max) {
       max = puzzle[i][j];
       n++;
     }
   }

   return n;
 }

 int visible_right(int puzzle[GRID_SZ][GRID_SZ], int i){
   int n = 0, j;
   int max = 0;

   if (puzzle[i][GRID_SZ-1] == 0)
     return n;

   for(j = GRID_SZ-1; j >= 0; j--){
     if (puzzle[i][j] > max) {
       max = puzzle[i][j];
       n++;
     }
   }

   return n;
 }

 int valid(int puzzle[GRID_SZ][GRID_SZ], int i, int j, int *clues){
   int t_clue = clues[j];
   int b_clue = clues[11-j];
   int l_clue = clues[15-i];
   int r_clue = clues[i+4];

   int visible_l = visible_left(puzzle, i);
   int visible_r = visible_right(puzzle, i);
   int visible_t = visible_top(puzzle, j);
   int visible_b = visible_bottom(puzzle, j);

   int x = 0;

   if (visible_r != 0){

     if (visible_l != l_clue && l_clue != 0){     
       return 0;
     }

     if (visible_r != r_clue && r_clue != 0){     
       return 0;
     }
   }

   if (visible_b != 0){
     if (visible_t != t_clue && t_clue != 0){     
       return 0;
     }

     if (visible_b != b_clue && b_clue != 0){     
       return 0;
     }
   }

   for (x = 0; x < GRID_SZ; x++) {
     if (j != x && puzzle[i][j] == puzzle[i][x]){     
       return 0; 
     }

     if (i != x && puzzle[i][j] == puzzle[x][j]){     
       return 0; 
     }
   }

   return 1; 
 }


 int **solve_helper(int puzzle[GRID_SZ][GRID_SZ], int i, int j, int *clues){
   int n;
   int **result;

   if (j >= GRID_SZ){
     j = 0;
     i = i + 1;
   }

   if (i >= GRID_SZ){
     result = malloc(GRID_SZ * sizeof(int*));
     for(i = 0; i < GRID_SZ; i++){
       result[i] = malloc(GRID_SZ * sizeof(int));
       for(j = 0; j < GRID_SZ; j++)
         result[i][j] = puzzle[i][j];
     }
     return result;
   } 

   for(n = 1; n < GRID_SZ+1; n++){
     puzzle[i][j] = n;
     if (valid(puzzle, i, j, clues)){
       result = solve_helper(puzzle, i, j+1, clues);
       if (result != NULL)
         return result;
       else
         puzzle[i][j] = 0;
     }
     else{
       puzzle[i][j] = 0;
     }
   }
   puzzle[i][j] = 0;
   return NULL;
 }

 int** SolvePuzzle (int *clues) {
   int puzzle[GRID_SZ][GRID_SZ];
   int i, j;
   int **result;

   for(i = 0; i < GRID_SZ; i++)
     for(j = 0; j < GRID_SZ; j++)
       puzzle[i][j] = 0;

   result = solve_helper(puzzle, 0, 0, clues);
   
   return result;
 }
