#include <iostream.h>
#include <time.h>
#include <conio.h>
int main() {
    int i = 1, j; char c;
    clock_t poc, kraj;
    cout << "Stisnite za pocetak stopanja!\n";
    //while(!kbhit());
    getch();
    poc = clock();
    cout << "Stisnite za kraj!\n";
    //while(!kbhit());
    //while(!kbhit()) {
    while( (j = ((kraj = clock())-poc)/CLK_TCK) < 100) {
        //cout << j << endl;
        if(kbhit()) break;
        if(j == i) {
          cout << "\r" << i;
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
    
    
    
