 import java.util.Vector;
 import java.util.Arrays;
 import java.util.List;

 public class Calculator {
   static enum Ops {ADD, SUB, MUL, DIV, NUM};
  
   static class Node{
     Ops op;
     Double value;
    
     Node(Double value){
       this.value = value;
       this.op = Ops.NUM;
     }
    
     Node(String s){
       this(new Double(Double.parseDouble(s)));
     }
    
     Node(char c){
       switch(c){
         case '-': this.op = Ops.SUB; break;
         case '+': this.op = Ops.ADD; break;
         case '*': this.op = Ops.MUL; break;
         case '/': this.op = Ops.DIV; break;
       }
       this.op = op;
     }
    
     Node(Ops op){
       this.value = 0.0;
       this.op = op;
     }
   }   
  
   static Vector<Node> parse(String expression){
     String s = "";
     Vector<Node> result = new Vector<Node>();
    
     for(char c : expression.toCharArray()){
       if (('0' <= c && c <= '9') || c == '.' || c == 'e' || c == 'E'){
         s += c;
       }
       else if (c == '+' || c == '*' || c == '/' || c == '-'){
         if (s.length() > 0)
           result.add(new Node(s));       
         result.add(new Node(c));       
         s = "";
       }         
     }
    
     if (s.length() > 0){         
       result.add(new Node(s));
     }
    
     return result;
   }
  
   static void negateNode(Vector<Node> expression, int index){
     Node tmp = expression.get(index);
     tmp.value *= -1;
     expression.set(index, tmp);
   }
  
   static void reduceOps(Vector<Node> expression){
     int i = 0;
     while(i < expression.size()){
       if (i == 0 && expression.get(0).op == Ops.SUB){         
         expression.remove(i);
         negateNode(expression, i);
       }
       else if (expression.get(i).op == Ops.SUB && expression.get(i-1).op == Ops.SUB){
         expression.remove(i-1);
         expression.set(i-1, new Node(Ops.ADD));
       }
       else if (expression.get(i).op == Ops.SUB && expression.get(i-1).op != Ops.NUM){
         expression.remove(i);
         negateNode(expression, i);
       }
       else{
         i++;
       }
     }
   }
  
   public static Double reducePair(Ops op, Double a, Double b){     
       switch(op){
         case SUB: return a - b;
         case ADD: return a + b;
         case MUL: return a * b;
         case DIV: return a / b;
       }     
       return 0.0;
   }
  
   public static void reduce(Vector<Node> expression, List<Ops> apply){
     int i = 0;   
     while(i < expression.size()){
       if (apply.contains(expression.get(i).op)){
         Double tmp = reducePair(expression.get(i).op, expression.get(i-1).value, expression.get(i+1).value);       
         expression.set(i+1, new Node(tmp));
         i--;
         expression.remove(i);
         expression.remove(i);
       }
       else {
         i++;
       }
     }
   }
  
   public static Double evaluate(String expression) {   
     Vector<Node> exp = parse(expression.replace(" ", ""));
     reduceOps(exp);
     reduce(exp, Arrays.asList(new Ops[]{Ops.MUL, Ops.DIV}));
     reduce(exp, Arrays.asList(new Ops[]{Ops.SUB, Ops.ADD}));
     return exp.get(0).value;
   }
 }