#include <cstdio>
#include <conio.h>
int polje[6][6], sol = 0;
void solve(int y, int x, int k) {
    //printf("(%d,%d)", y, x); 
    if(k == 6) {
    bool da = true;
    for(int i = 0; i < 6; i++) {
      int red = 0, st = 0;
      for(int j = 0; j < 6; j++) 
          red += polje[i][j];
      for(int l = 0; l < 6; l++)
         st+= polje[l][i];
      if(red%2 || st%2) {da = false; break;}
    }    
    if(da) {
        for(int i = 0; i < 6; i++) {
           for(int j = 0; j < 6; j++)
             printf("%2d", polje[i][j]);   
            printf("\n");
        }
        printf("\n"); getch();
        sol++; 
    }   
    }  
          

    for(int j = y; j < 6; j++)
      for(int i = 0; i < 6; i++) {
          if(k < 6 && (y != j || i > x) && !polje[j][i]) {
            polje[j][i] = 1;
            solve(j, i, k+1);
            polje[j][i] = 0;
          }
      }        
}    
int main() {
    solve(0, -1, 0);
    printf("%d", sol);
   int tmp; scanf("%d", &tmp);
    return 0;
}    
