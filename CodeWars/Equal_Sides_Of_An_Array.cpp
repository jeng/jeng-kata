 #include <vector>
 using namespace std;

 int sum(const vector<int> numbers, int start, int stop){
   int r = 0;   
   for(int i = start; i < stop; i++) {
     r += numbers[i];
   }
   return r;
 }

 int find_even_index (const vector <int> numbers) {
   for (int i = 0; i < numbers.size(); i++){
     if (sum(numbers, 0, i) == sum(numbers, i+1, numbers.size()))
       return i;
   }
   return -1;
 }
