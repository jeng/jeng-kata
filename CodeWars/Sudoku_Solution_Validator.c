 #include<stdbool.h>

 #define TARGET (123456789)

 int pack(int num, int aggregate){
   int offset = 9 - num;
   if (offset == 0){
     return aggregate + 9;
   }
   else{
     return aggregate + (num * pow(10, offset));
   }
 }

 bool checkRowsAndColumns(unsigned int board[9][9]){
   for(int i = 0; i < 9; i++){
     int a = 0;
     int b = 0;
     for(int j = 0; j < 9; j++){
       int n = board[j][i];
       int m = board[i][j];
       if (0 < n && n <= 9){
         a = pack(n, a);
       }
       else{
         return false;
       }
       if (0 < m && m <= 9){
         b = pack(m, b);
       }
       else {
         return false;
       }
     }
     if (a != TARGET || b != TARGET){
       return false;
     }     
   }
   return true;
 }

 bool checkGroup(int gid, unsigned int board[9][9]){
   int start_row[9] = {0,0,0,3,3,3,6,6,6};
   int start_col[9] = {0,3,6,0,3,6,0,3,6};
   int a = 0;
   int sr = start_row[gid];
   int sc = start_col[gid];
   for(int i = sr; i < sr + 3; i++){
     for(int j = sc; j < sc + 3; j++){
       int n = board[i][j];
       if (0 < n && n <= 9){
         a = pack(n, a);
       }
       else {
         return false;
       } 
     }
   }
   return (a == TARGET); 
 }

 bool validSolution(unsigned int board[9][9]){
    if (!checkRowsAndColumns(board)){
      return false;
    }
    for(int i = 0; i < 9; i++){
      if (!checkGroup(i, board)){
        return false;
      }
    }
    return true;
 }
