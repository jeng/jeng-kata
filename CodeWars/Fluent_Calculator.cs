 using System.Collections.Generic;

 namespace Kata
 {
     class FluentCalculator {
       private Stack<string> expression;

       public FluentCalculator Zero{
         get{
           expression.Push("0");
           return this;
         }
       }
       public FluentCalculator One{
         get{
           expression.Push("1");
           return this;
         }
       }
       public FluentCalculator Two{
         get{
           expression.Push("2");
           return this;
         }
       }
       public FluentCalculator Three{
         get{
           expression.Push("3");
           return this;
         }
       }
       public FluentCalculator Four{
         get{
           expression.Push("4");
           return this;
         }
       }
       public FluentCalculator Five{
         get{
           expression.Push("5");
           return this;
         }
       }
       public FluentCalculator Six{
         get{
           expression.Push("6");
           return this;
         }
       }
       public FluentCalculator Seven{
         get{
           expression.Push("7");
           return this;
         }
       }
       public FluentCalculator Eight{
         get{
           expression.Push("8");
           return this;
         }
       }
       public FluentCalculator Nine{
         get{
           expression.Push("9");
           return this;
         }
       }
       public FluentCalculator Ten{
         get{
           expression.Push("10");
           return this;
         }
       }
    
       public FluentCalculator Plus{
         get{
           expression.Push("+");
           return this;
         }
       }
    
       public FluentCalculator Minus{
         get{
           expression.Push("-");
           return this;
         }
       }
    
       public FluentCalculator Times{
         get{
           expression.Push("*");
           return this;
         }
       }
    
       public FluentCalculator DividedBy{
         get{
           expression.Push("/");
           return this;
         }
       }
              
       public double Result(){       
         if (expression.Count > 0){

           expression = new Stack<string>(expression);

           Stack<string> pass1 = new Stack<string>();
          
           //Pass1
           while(expression.Count != 0){
             //Reduce the muls and divs           
             string s= expression.Peek();
             expression.Pop();

             if (s == "*")
             {               
               double d = double.Parse(pass1.Peek());
               double d1 = double.Parse(expression.Peek());
               pass1.Pop();
               expression.Pop();
               pass1.Push((d * d1).ToString());             
             }
             else if (s == "/")
             {
               double d = double.Parse(pass1.Peek());
               double d1 = double.Parse(expression.Peek());
               pass1.Pop();
               expression.Pop();
               pass1.Push((d / d1).ToString());
             }
             else {
               pass1.Push(s);
             }
           }
          
           pass1 = new Stack<string>(pass1);

           //Pass2
           while(pass1.Count != 0){
             string s= pass1.Pop();
             if (s == "+")
             {               
               double d = double.Parse(expression.Peek());
               double d1 = double.Parse(pass1.Peek());
               pass1.Pop();
               expression.Pop();
               expression.Push((d + d1).ToString());
             }
             else if (s == "-")
             {
               double d = double.Parse(expression.Peek());
               double d1 = double.Parse(pass1.Peek());
               pass1.Pop();
               expression.Pop();
               expression.Push((d - d1).ToString());
             }
             else {
               expression.Push(s);
             }
           }

           double res = double.Parse(expression.Peek());
           expression.Clear();
           return res;
         }
        
         return 0;//TODO what to do if we just get a call to result? Throw?   
       }
    
       public static implicit operator double(FluentCalculator fc)
       {
         return fc.Result();
       }

       public FluentCalculator(){
         expression = new Stack<string>();       
       }
     }   
 }
