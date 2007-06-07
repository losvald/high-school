#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#define MAX 200
using namespace std;
int n;
double a[MAX][MAX], sol[MAX];
char var_name[MAX+1], nvar;
void input() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n+1 ; ++j)
      scanf("%lf", &a[i][j]);
}
void ispis() {
  for(int i = 0; i < n; ++i) {
    printf("|");
    for(int j = 0; j < n+1; ++j) {
      printf("%5.1lf", a[i][j]);
    }
    printf("|\n");
  }
  printf("\n");    
}
void get_sol() {
  for(int i = 0; i < n; ++i)
    printf("%c = %5.2lf\n", var_name[i], sol[i]); 
}
int get_name(char c) {
  for(int i = 0; i < nvar; ++i)
    if(var_name[i] == c) return i;
  var_name[nvar] = c;
  return nvar++;
}  
void upis() {
  printf("Upisi n - broj jednadzbi tj. max broj nepoznanica,");
  printf("i zatim n jednadzbi (bez razmaka), broj bez nepoznanice mora biti na desnoj strani,");
  printf("na lijevoj moze biti bilo sto osim broja bez nepoznanice.\n");
  printf("npr.\n3\n-17x+3y-0.5z=0.5\nz-0.5y=14\ny+x+z=20\n\n");
  scanf("%d", &n);
  fflush(stdin);
  for(int row = 0; row < n; ++row) {
    char s[MAX*10];
    gets(s);
    int len = strlen(s);
    for(int i = 0; i < len; ++i) {
      if(s[i] == '=') continue;
      char broj[20]; double val = 0;
      int lenbr = 0;
      if(s[i] == '-') val = -1;
      else if(s[i] == '+') val = 1;
      for(; isdigit(s[i]) || (!lenbr && s[i] == '+' || s[i] == '-' || s[i] == '.'); ++i) 
        broj[lenbr++] = s[i];  
      broj[lenbr] = '\0';
      if(!lenbr) val = 1;
      else if(atof(broj) || lenbr > 1) val = atof(broj);
      int var = n;
      if(s[i] >= 'A' && s[i] <= 'z') 
        var = get_name(s[i]);
      a[row][var] += val;
    }  
  }  
}    
void back_supstitute() {
  for(int i = n-1; i >= 0; --i) {
    double res = a[i][n];
    for(int j = i+1; j < n; ++j)
      res -= sol[j]*a[i][j];
    sol[i] = res/a[i][i];
  }  
}  
void row_swap(int r1, int r2) {
  //printf("(%d <-> %d)\n", r1, r2);
  for(int i = 0; i < n+1; ++i)
    swap(a[r1][i], a[r2][i]);
}   
void gauss() {
  for(int i = 0, j = 0; i < n && j < n; ++j) {
    i = j;
    int maxi = i;
    for(int k = i+1; k < n; ++k)
      if(abs(a[k][j]) > abs(a[maxi][j]))
        maxi = k;
    if(abs(a[maxi][j]) > 1e-5) {
      row_swap(maxi, i);
      double piv = a[i][j];
      for(int col = 0; col < n+1; ++col) a[i][col] /= piv;
      for(int u = i+1; u < n; ++u) {
        //row substract
        double pj = a[u][j];
        for(int col = 0; col < n+1; ++col)
          a[u][col] -= pj * a[i][col];
      }
      ++i;  
    } 
  }
  back_supstitute();  
}   
int main() {
  upis();
  double st = clock();
  gauss();
  //ispis();
  get_sol();
  printf("\n (%lf ms)\n", clock()-st);
  scanf("\n");
  return 0;
}
/*
4
.1 -0.5 0 1 2.7
0.5 -2.5 1 -0.4 -4.7
1 0.2 -0.1 .4 3.6
.2 .4 -0.2 0 1.2

4
0.1a-0.5b+d=2.7
.5a-2.5b+c-0.4d=-4.7
a+0.2b-0.1c+0.4d=3.6
.2a+0.4b-0.2c=1.2 

3
 2  1 -1  8
-3 -1  2 -11
-2  1  2 -3

3
y+2x-z=8
y-2x+2z=-3
-3x+2z-y=-11

2
x+5x-y=5
x+y=3


*/


