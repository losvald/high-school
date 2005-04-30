#include <stdio.h>
#include <conio.h>
#include <iostream.h>
double fact(double x) {
    double suma = 1;
    while(x > 1)
      suma*=x--;
    return suma;
}    
double c(int N, int K) {
    //cout << fact(N) << " " << fact(K) << " " << fact(N-K);
    return fact(N)/(fact(K)*fact(N-K)); 
}    
int main() {
    int n, k, m, s;
    cout << "Upisite redom: 1. broj pogodjenih brojeva" << endl
         << "               2. broj max pogodaka" << endl
         << "               3. broj krizanja brojeva" << endl
         << "               4. broj polja u lottu. " << endl;
    cin >> m >> k >> s >> n;
    cout << (long long int) (c(n, k)/( c(s, m)*c(n-s, k-m) ) ) << endl;
    getch();
    return 0;
}    
