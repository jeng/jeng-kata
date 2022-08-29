unordered_map<int, int> mem; 
int specialPower(int n){
  int r = 0;
  int key = n;
  while(n != 1){
    if (mem.find(n) != mem.end()){
      mem[key] = r + mem[n]; 
      return mem[key];
    }
    if (n % 2 == 0){
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    r++;
  }
    mem[key] = r;
    return mem[key];
}
int powerCompare(int a, int b){
  int pa = specialPower(a);
  int pb = specialPower(b);
  if (pa == pb){
    return (a < b);
  }
  return (pa < pb);
}
class Solution {
public:
    int powerSort(int start, int stop, int k){
      vector<int> ls;
      for(int i = start; i <= stop; i++){
        ls.push_back(i);
      }
      sort(ls.begin(), ls.end(), powerCompare);
      return ls[k];
    }
    int getKth(int lo, int hi, int k) {
        return powerSort(lo, hi, k-1);
    }
};