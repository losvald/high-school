#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <conio.h>
double prav(int a, int b) {
    double rez;    
    for(int i = 1; i <= a; i++) {
        for(int j = 1; j <= b; j++) {
            rez += (a - i + 1)*(b - j + 1);
            //cout << i << "," << j << ": " << temp << endl;
        }
    }
    return rez;
}                
int main() {
    int m, n, br = 1;
    double temp, rez = 0;
    ofstream out("pravokutnici.txt", ios::out);
    out << "BROJAC PRAVOKUTNIKA v1.0\t by LEO OSVALD" << endl << endl;
    for(int puta = 0; puta < 3; puta++)
      out << setw(5) << "Dimen" << " - broj prav." << " | ";
    out << endl;
    for(m = 1; m < 45; m++) {
        for(n = m; n < 45; n++) {
          out << setw(2) << m << "," << setw(2) << n << " - " << setw(10) << prav(m, n) << " | ";
          if(br++ % 3 == 0) out << endl;
        }
    }        
    getch();
}            
