#include <iostream.h>
#include <time.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
int val[15]; id = 
int main() {
    int i = 1, j; char c;
    int max;
    clock_t poc, kraj;
    max = 15;
    poc = clock();
    while( (j = ((kraj = clock())-poc)/CLK_TCK) < 100) {
        if(kbhit() || max-i == 0) break;
        if(j == i) {
          cout << "\r" << max-i << "  ";
          if(max-i <= 5) cout << "\07";
          i++;
        }    
    }
        
    getch();
    return 0;
}    
    
