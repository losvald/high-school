#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
int a, b, c, k, eb, ab, bb, cb, kb, sol;
string base(int x, int b) {
  string ret;
  char buff[10];
  int ok = 0;
  if(b == 2) {
    for(int i = 31; i >= 0; --i) {
      ok |= !!((1 << i) & x);
      if(ok || !i) ret.push_back('0'+!!((1 << i) & x)); 
    }  
  }
  else if(b == 8) {
    sprintf(buff, "%o", x);
    ret = buff;
  }
  else if(b == 16) {
    sprintf(buff, "%x", x);
    ret = buff;
  }
  else ret = buff;    
  return ret;    
} 
void gen() {
  const int bases[] = {2, 8, 16};
  srand(time(0));
  a = rand()%300; 
  b = rand()%300;
  do {
    c = rand()%300;
  } while(a+b-c < 2);  
  k = 1;
  eb = bases[rand()%3];
  ab = bases[rand()%3];
  bb = bases[rand()%3];
  cb = bases[rand()%3];
  kb = bases[rand()%3];
  printf("Express X as %d-base number:\n", eb);
  int r = a + b - c;  
  for(k = 2; r%k ; ++k) ;  
  printf("%s(%d)*X + %s(%d) = %s(%d) + %s(%d)", base(k, kb).c_str(), kb, base(c, cb).c_str(), cb,
    base(a, ab).c_str(), ab, base(b, bb).c_str(), bb);
  sol = r/k;
}   
void solve() {
  printf("\nPritisni Enter za rjesenje."); cin.get();
  printf("Solution: %s\n((%d + %d - %d) / %d = %d)", base(sol, eb).c_str(), a, b, c, k, sol);
}  
int main() {
  gen();
  solve(); 
  scanf("\n");
  return 0;
}  
