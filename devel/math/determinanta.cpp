#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>
#define MAXN 25
#define MAX 30
using namespace std;
const int inf = 1000000000;
int n;
double a[MAX][MAX], memo[1 << MAXN];
void init() {
  for(int i = 0; i < 1 << MAXN; ++i) memo[i] = inf; 
}  
void input() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n ; ++j)
      scanf("%lf", &a[i][j]);
}
void ispis(int mask, int k) {
  for(int i = 0; i < k; ++i) {
    printf("|");
    for(int j = 0; j < n; ++j) {
      if(mask & (1 << j)) continue;
      printf("%5.1lf", a[n-k+i][j]);
    }
    printf("|\n");
  }
  printf("\n");    
}  
int first(int x) {
  for(int i = 0; i < n; ++i) 
    if((x & (1 << i)) == 0) return i;
  return 0;
}
double rec(int mask, int k) {
  //ispis(mask, k);
  if(mask <= (1 << MAXN) && memo[mask] != inf) return memo[mask];
  if(k == 1) return /*memo[mask] = */a[n-1][first(mask)];
  int pred = -1;
  double ret = 0;
  for(int st = 0; st < n; ++st) {
    if(mask & (1 << st)) continue;
    else pred = -pred;
    //printf("%d * \n", pred*a[n-k][st]);
    ret += pred*a[n-k][st] * rec(mask | (1 << st), k-1);
  }
  if(mask <= (1 << MAXN)) memo[mask] = ret;
  return ret;
  //return memo[mask] = ret;   
}    
int main() {
  init();
  input();
  double st = clock();
  printf("Rezultat: %lf", rec(0, n));
  printf("\n (%lf ms)", clock()-st);
  scanf("\n");
  return 0;
}
/*
3
1.0  0.3 -0.7
0.0  1.0 -1.0
0.0  0.0  1.0

3
2 1 -1
0 .5 .5
0 0 -1
*/
/*
5
1 4 6 2 3
6 5 2 1 1
7 6 2 3 4
7 8 1 1 2
4 4 6 8 9

4
2 2 3 4
5 6 17 8
4 10 10 12
13 14 15 16

10
1 2 7 6 6 2 1 3 4 5
3 1 2 1 7 8 1 5 3 4
3 2 2 1 7 8 1 1 3 4
3 3 7 1 7 8 2 1 3 4
3 3 6 3 2 1 4 2 2 4
1 1 4 3 2 5 2 1 2 4
1 3 4 5 4 4 7 2 2 6
9 9 2 2 3 3 7 8 8 8
1 3 4 5 2 4 6 2 2 6
1 2 4 5 2 4 6 9 2 6

20
1 2 7 6 6 2 1 3 4 5 7 6 2 3 5 7 8 2 3 7
3 1 2 1 7 8 1 5 3 4 3 1 2 1 7 8 1 5 3 4
3 2 2 1 7 8 1 1 3 4 1 3 4 5 2 4 6 2 2 6
3 3 7 1 7 8 2 1 3 4 1 2 7 6 6 2 1 3 4 5
3 3 6 3 2 1 4 2 2 4 1 3 4 5 4 4 7 2 2 6
1 1 4 3 2 5 2 1 2 4 1 3 4 5 4 4 7 2 2 6
1 3 4 5 4 4 7 2 2 6 3 3 7 1 7 8 2 1 3 4
9 9 2 2 3 3 7 8 8 8 3 3 7 1 7 8 2 1 3 4
1 3 4 5 2 4 6 2 2 6 3 3 7 1 7 8 2 1 3 4
1 2 4 5 2 4 6 9 2 6 1 2 7 6 6 2 1 3 4 5
1 2 7 6 6 2 1 3 4 5 3 2 2 1 7 8 1 1 3 4
3 1 2 1 7 8 1 5 3 4 9 9 2 2 3 3 7 8 8 8
3 2 2 1 7 8 1 1 3 4 3 3 6 3 2 1 4 2 2 3
3 3 7 1 7 8 2 1 3 4 3 3 6 3 2 1 4 2 2 4
3 3 6 3 2 1 4 2 2 4 3 4 5 2 4 6 2 2 6 3
1 1 4 3 2 5 2 1 2 4 1 3 4 5 2 4 6 2 2 6
1 3 4 5 4 4 7 2 2 6 1 3 4 5 2 4 6 2 2 6
9 9 2 2 3 3 7 8 8 8 1 7 8 1 5 3 4 9 9 2
1 3 4 5 2 4 6 2 2 6 2 6 5 2 2 1 1 2 3 5
1 2 4 5 2 4 6 9 2 6 1 7 8 1 5 3 4 9 9 1
*/


