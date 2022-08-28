 function meanMaxQM(faces, rolls) {
   const matrix = new Array(rolls).fill(1).map(() => new Array(faces).fill(1)); 
   for(let i = 1; i < rolls; i++){   
     for(let j = 1; j < faces; j++){
       matrix[i][j] = matrix[i][j-1] + matrix[i-1][j]
     }
   }
   sum = 0;
   denom = 0;
   n = 1;
   single = 0;
   for(let i = 0; i < faces; i++){
     single += matrix[0][i] * n;
     sum += matrix[rolls-1][i] * n++;
     denom += matrix[rolls-1][i];   
   } 
   return (sum/denom) - (single/faces); 
 }
