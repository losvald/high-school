#include <iostream.h>
#include <time.h>
#include <conio.h>
int main() {
    int i = 1, j; char c;
    int max;
    clock_t poc, kraj;
    cout << "Stisnite za pocetak odbrojavanja i unesite vrijeme u sec!\n";
    scanf("%d", &max);
    max++;
    //while(!kbhit());
    //getch();
    poc = clock();
    cout << "Stisnite za kraj!\n";
    //while(!kbhit());
    //while(!kbhit()) {
    while( (j = ((kraj = clock())-poc)/CLK_TCK) < 100) {
        //cout << j << endl;
        if(kbhit() || max-i == 0) break;
        if(j == i) {
          cout << "\r" << max-i << "  ";
          if(max-i <= 5) cout << "\07";
          i++;
        }    
    }    
    //}
    //getch();
    kraj = clock();
    cout << "\nInterval je trajao " << (kraj-poc)/CLK_TCK/1. << " s";
    getch();
    getch();
    return 0;
}    
    
    
    
