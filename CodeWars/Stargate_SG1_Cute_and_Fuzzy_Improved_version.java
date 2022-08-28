  import java.util.*;
 
  class Pos{
   int x;
   int y;
   Pos(int x, int y){
     this.x = x;
     this.y = y;
   }
   public String toString(){
     return "(" + x + ", " + y + ")";
   }     
 }

 class Node implements Comparable<Node>{
   double weight;
   double deltaGoal;
   double deltaStart; 
   int x;
   int y;
   int prevX;
   int prevY;
  
   Node(int x, int y, int prevX, int prevY, double deltaGoal, double deltaStart){
     this.x = x; this.y = y; this.prevX = prevX; this.prevY = prevY;
     this.deltaGoal = deltaGoal; this.deltaStart = deltaStart;   
     this.weight = deltaGoal + deltaStart;
   }
  
   public double getWeight(){
     return weight;
   }
  
   public int compareTo(Node n)
   {
       if (weight < n.getWeight())
         return -1;
       else if (weight > n.getWeight())
         return 1;
       else
         return 0;
   }
     
     @Override
     public boolean equals(Object o) {
         if (o == this) {
             return true;
         }
  
         if (!(o instanceof Node)) {
             return false;
         }         
        
         Node c = (Node) o;          
         return (this.x == c.x && this.y == c.y);
     }
  
   @Override
   public int hashCode() {
     return x * 10000 + y;
   }

 }

 enum Direction{
   North,
   South,
   East,
   West, 
   NorthWest,
   NorthEast, 
   SouthWest,
   SouthEast,   
 }

 public class SG1 {

   private static int getWidth(String wires){
     for(int i = 0; i < wires.length(); i++){
       if (wires.charAt(i) == '\n')
         return i;
     }
     return 0;
   }
  
   private static int getHeight(String wires){
     int w = getWidth(wires);
     return wires.length() / w;
   }
  
   private static char getPos(String wires, int x, int y, int w, int h){
     int idx = y * (w + 1) + x;//Add one to the width to account for new lines   
     return wires.charAt(idx);   
   }
  
   //Wishing java had ref parameters for primative types
   //or, if I'm just dreaming about things, multiple value bind.
   //Passing an object so it can be treated as mutable is nasty.
   //Creating a bunch of garbage on the heap is nasty.
   private static Pos move(int x, int y, Direction dir){
     switch (dir){
       case North: return new Pos(x, y-1);
       case South: return new Pos(x, y+1);
       case East: return new Pos(x+1, y);
       case West: return new Pos(x-1, y);
       case NorthWest: return new Pos(x-1, y-1);
       case NorthEast: return new Pos(x+1, y-1);
       case SouthWest: return new Pos(x-1, y+1);
       case SouthEast: return new Pos(x+1, y+1);    
     }
     return new Pos(-1, -1);
   }
  
   private static boolean validPos(String wires, int x, int y, int w, int h){
     if (x < 0 || y < 0)
       return false;
     if (x >= w || y >= h)
       return false;
     char c = getPos(wires, x, y, w, h);
     if (c == 'X')
       return false;
     return true;
   }
  
   private static Pos findSymbol(String wires, char symbol, int w, int h){
     for(int y = 0; y < h; y++){
       for(int x = 0; x < w; x++){
         char c = getPos(wires, x, y, w, h);
         if (c == symbol){
           return new Pos(x, y);
         }
       }     
     }
     return new Pos(-1, -1);
   }
  
   private static Pos findStart(String wires, int w, int h){
     return findSymbol(wires, 'S', w, h);
   }

   private static Pos findGoal(String wires, int w, int h){
     return findSymbol(wires, 'G', w, h);
   }
  
   private static double distance(float x1, float y1, float x2, float y2){
     float km_per_sq = 1;
     float center = km_per_sq/2;
     float sx1 = km_per_sq * x1 + center;
     float sx2 = km_per_sq * x2 + center;
     float sy1 = km_per_sq * y1 + center;
     float sy2 = km_per_sq * y2 + center;   
     float dx = sx2 - sx1;
     float dy = sy2 - sy1;
     return Math.sqrt((dx * dx) + (dy * dy));
   }

   public static String wireDHD(String existingWires) {
    
         Hashtable<Node, Double> weightHistory = new Hashtable<Node, Double>();
         PriorityQueue<Node> queue = new PriorityQueue();
         int w = getWidth(existingWires);
         int h = getHeight(existingWires);
         Pos history[] = new Pos[w * h];
         if (w == 0 && h == 0)
           return "Oh for crying out loud...";
          
         Pos start = findStart(existingWires, w, h);
         Pos goal = findGoal(existingWires, w, h);

         Node current = new Node(start.x, start.y, start.x, start.y, distance(start.x, start.y, goal.x, goal.y), 0);
         queue.add(current);
        
         while(queue.size() > 0 && !(current.x == goal.x && current.y == goal.y)){
           current = queue.poll();
            
           int historyIdx = current.y * w + current.x;
           if (history[historyIdx] == null){
             history[historyIdx] = new Pos(-1, -1);
           }
          
           history[historyIdx].x = current.prevX;
           history[historyIdx].y = current.prevY;         

           if (current.x == goal.x && current.y == goal.y)
             break;

           for(Direction dir : Direction.values()){
             Pos neighbor = move(current.x, current.y, dir);
             if (validPos(existingWires, neighbor.x, neighbor.y, w, h) &&                            
                   history[((neighbor.y * w) + neighbor.x)] == null){
                                
                 Node node = new Node(neighbor.x, neighbor.y,
                     current.x, current.y,
                     distance(goal.x, goal.y, neighbor.x, neighbor.y),
                     current.deltaStart + distance(current.x, current.y, neighbor.x, neighbor.y));
                
                 if (queue.contains(node)){
                   if (weightHistory.get(node) > node.getWeight()){
                     queue.remove(node);
                     queue.add(node);
                     weightHistory.put(node, node.getWeight());
                   }                   
                 }
                 else{                 
                   queue.add(node);
                   weightHistory.put(node, node.getWeight());
                 }                 
             }       
           }         
         }

         if (current.x == goal.x && current.y == goal.y){
           StringBuilder result = new StringBuilder(existingWires);
           int x = history[current.y * w + current.x].x;
           int y = history[current.y * w + current.x].y;
  
           while(getPos(existingWires, x, y, w, h) != 'S'){
             result.setCharAt(y * (w + 1) + x, 'P');
             int histIdx = y * w + x;
             x = history[histIdx].x;
             y = history[histIdx].y;
           }         
                    
           return result.toString();
         }
        
         return "Oh for crying out loud...";     
     }
 }
