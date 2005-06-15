#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
struct rezultati {
    int n_norm;
    int n_obr;
} rez;    
double comb(int x, int z = 2) {
    double y, suma = 1, rez1 = 1, rez2 = 1, rez3 = 1;
    if((y = x-z) < 1) y = 1;
    while (x > 1) 
        rez1*=x--;
    while (y > 1)
        rez2*=y--;
    while (z > 1)
        rez3*=z--;
    suma = rez1/(rez2*rez3);
    return suma;
}
double zbroj(int x, int y) {
    double suma = 0, t;
    t = x - y + 1;
    while (t > 0) 
      suma+=t--;
    t = x - y - y + 1;
    while (t > 0)
      suma+=t--;
    return suma;
}           
int main() {
    int t_paran = 0, t_neparan = 0;
    ofstream out("trokuti.txt",  ios::out);
    out << "BROJAC TROKUTA v1.1\tby LEO OSVALD" << endl << endl;
    out << setw(2) << "br" << " - " << setw(7) << "norm" << " " << setw(7) << "obrn" 
             << "  " << setw(6) << "ukupno" << " | " << setw(6) << "(1.)" << setw(6) 
             << "(2.)" << setw(6) << "(3.)" << setw(6) << "(4.)" << setw(6) << "(5.)"
             << setw(6) << "(6.)" << setw(6) << "(7.)" << endl;
             
    for(int i = 1; i < 100; i++) {
        if(i%2 != 0)  {
            t_neparan += (int) comb(i);
            rez.n_obr = t_neparan;
        }    
        else {
            t_paran += (int) comb(i);
            rez.n_obr = t_paran;
        }    
        rez.n_norm = (int) comb(i+2, 3);
        out << setw(2) << i << " - " << setw(7) << rez.n_norm << " " << setw(7) << rez.n_obr 
             << " " << setw(7) << rez.n_norm + rez.n_obr << " | " << setw(6)
             << zbroj(i, 1) << setw(6) << zbroj(i,2) << setw(6) << zbroj(i,3) << setw(6)
             << zbroj(i, 4) << setw(6) << zbroj(i, 5) << setw(6) << zbroj(i, 6) << setw(6)
             << zbroj(i, 7) << endl;
    }    
        
    getch();
    return 0;
}    
