#include <cstdio>
#include <iostream.h>
#include <ctime>
#include <conio.h>
int main() {
    clock_t poc, kraj, t1, t2;
    poc = clock();
    for(int i = 0; i < 10000; i++) cout << i*10 << endl;
    kraj = clock();
    cout << "Svako prolaz petlje trajao je u prosjeku " << (kraj-poc)/CLK_TCK/10000.
    << " s" << endl;
    cout << 10./99 << " " << 10/99;
    cout << "\npocinje...";
    t1 = clock();
    t2 = clock();
    while((t2-t1)/CLK_TCK < 10)
      t2 = clock();
    cout << (t2-t1)/CLK_TCK/1. << endl;  
    getch();
    return 0;
}    
