#include <cstdio>
#include <ctime>
#include <math.h>
#include <cstdlib>
FILE *f;
#define fo "andrej.txt"
#define MAX 10000000
bool polje[MAX];
int main() {
    int n, k = 1000; double st; bool da,d1= true,d2=true,d3=true;
    f = fopen(fo, "w");
    //scanf("%d", &n);
    fprintf(f,"   n                 ms");
    for(n = 1000; n <= 10000000; n+= k) {
      double st1 = clock(); int br = 0;
      fprintf(f,"%8d - ",n); printf("%d\n", n);
      if(d1) {
      for(int i = 2; i*i <= n; i++)
        for(int j = 2; j*i <= n; j++)
          if(!polje[i*j]) polje[i*j] = true;
       ///for(int i = 2; i <= n; i++) if(!polje[i]) br++;//printf("%d ", i);
       fprintf(f,"%7.2lf", st1 = clock()-st1);
       //printf("%.2lf ms (%d)\n", st1 = clock()-st1, br);
       if(st1 > 5000) st = false;
    }    
    if(d2) {
      double st2 = clock(); br = 0;
      for(int i = 2; i <= n; i++) {
        da = true;
        for(int j = 2; j <= trunc(sqrt(i)); j++)
          if(i % j == 0) {da = false; break;}
        //if(da) printf("%d ", i); 
      }
      fprintf(f,"%12.2lf\t", st2 = (clock()-st2));     
      //printf("%.2lf ms (%d)\n", st2 = clock()-st2, br);
      if(st2 > 5000) d2 = false;
    }
    if(d3) {    
      double st3 = clock(); br = 0;
      for(int i = 2; i <= n; i++) {
        da = true;
        for(int j = 2; j <= i-1; j++)
          if(i % j == 0) da = false;
      }
      fprintf(f,"%12.2lf", st3 = (clock()-st3));
      //printf("%.2lf ms (%d)\n", st3 = clock()-st3, br); 
      if(st3 > 5000) d3 = false;
    }
    fprintf(f,"\n");
    if(n == 10000 || n == 100000 || n == 1000000) k*=10;      
  }
    fclose(f);  
    return 0;
}    
