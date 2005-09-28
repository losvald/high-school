#include <iostream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip.h>
int main() {
    double i = 1, j; char c;
    double poc, kraj;
    cout << "Stisnite za pocetak stopanja!\n";
   
    getch();
    poc = clock();
    cout << "Stisnite za kraj!\n";
    while( (j = ((kraj = clock())-poc)) < 10000000) {
        
        if(kbhit()) break;
        printf("\r%6.0lf ms", j);  
        //if((int)j%1000 == 0) printf("\07");
        
    }    

    kraj = clock();
    cout << "\nInterval je trajao " <<(kraj-poc)/1. << " ms.";
    /*for(int i = 0; i < 255; i++)
     printf("%d %c\t", i, i);*/
    getch();
    getch();
    return 0;
}    
    
    
    
