#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <time.h>
int main() {
    char tekst[1000], c; int i, j, k = 0;
    
    cout << "Upisite tekst: ";
    for (i=0;i < 999 && (c = getchar()) != EOF && c!='\n'; ++i) 
      tekst[i] = c;
    tekst[i] = '\0';
    cout << "\nPritisnite kada zelite da pocne!" << endl;
    getch();
    clock_t poc, kraj;
    poc = clock();
    i = 0;
    while( (j = ((kraj = clock())-poc)/CLK_TCK) < 1000) {
        if(kbhit()) break;
        if(j == i) {
          if(tekst[i] == '\0') break;  
          cout << tekst[i++];
        }    
    }    
    getch();
    getch();
    return 0;
}    
