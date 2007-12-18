#include <cstdio>
#include <iostream>
#include <list>
using namespace std;
list<int> a;
int n, k, len;
void construct() {
  len = n;
  for(int i = 1; i <= n; ++i) a.push_back(i);
}
template<typename T> //templejtirana funkcija move - radi kruzne liste
void move(T& x) { if(++x == a.end()) x = a.begin(); }   
int solve() {
  for(list<int>::iterator p = a.end(); len > 1; --len) {
    int korak = (k-1) % len;
    for(int i = 0; i < korak; ++i) move(p);
    list<int>::iterator pom = p;
    move(pom);
    a.erase(pom);
  }  
  return a.front();  
}  
int main() {
  printf("Upisi n (broj elemenata): "); scanf("%d", &n);
  printf("Upisi k (kojeg k-tog krizas): "); scanf("%d", &k);
  construct();
  printf("Rjesenje: %d\n", solve());
  scanf("\n");
  return 0;
}


