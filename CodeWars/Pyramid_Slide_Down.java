 public class LongestSlideDown {
      
     static enum Direction { Left, Right };
     static class DirectionNode{
       int value;
       Direction direction;
       DirectionNode(Direction direction, int value){
         this.direction = direction;
         this.value = value;
       }
     }
    
     public static int longestSlideDown(int[][] pyramid) {
         DirectionNode [][] workingPyramid;
         workingPyramid = new DirectionNode[pyramid.length][];
        
         for(int i = 0; i < pyramid.length; i++){
           workingPyramid[i] = new DirectionNode[pyramid.length];
           for(int j = 0; j < pyramid[i].length; j++){
             int leftIndex  = j - 1;
             int rightIndex = j;
                        
             int parentIndex = i - 1;
            
             // Should probably do a sanity check here to make sure the top of the
             // pyramid only has a single item
             if (parentIndex < 0) {
               workingPyramid[0][0] = new DirectionNode(Direction.Right, pyramid[0][0]);
               continue;
             }
            
             int leftValue = 0;
             if (0 <= leftIndex) {
               leftValue = workingPyramid[parentIndex][leftIndex].value;
             }
            
             int rightValue = 0;
             if (rightIndex < workingPyramid[parentIndex].length &&
                 workingPyramid[parentIndex][rightIndex] != null){             
               rightValue = workingPyramid[parentIndex][rightIndex].value;
             }
            
             rightValue += pyramid[i][j];
             leftValue  += pyramid[i][j];
              
             if (rightValue <= leftValue){
               workingPyramid[i][j] = new DirectionNode(Direction.Left, leftValue);
             }
             else {
               workingPyramid[i][j] = new DirectionNode(Direction.Right, rightValue);
             }             
           }           
         }
                
         // get the starting point
         int startRow = workingPyramid.length -1;
         int column = 0;
         int maxVal = 0;
         for(int i = 0; i < workingPyramid[startRow].length; i++){
           if (workingPyramid[startRow][i].value > maxVal){
             maxVal = workingPyramid[startRow][i].value;
             column = i;
           }           
         }

         // walk the tree backwards
         // use the index from the walk to pull the original values
         int sum = 0;
         for(int i = startRow; i >= 0; i--){
           System.out.println(pyramid[i][column]);
           sum += pyramid[i][column];
           if (workingPyramid[i][column].direction == Direction.Left)
             column--;
         }
         return sum;
     }
 }
