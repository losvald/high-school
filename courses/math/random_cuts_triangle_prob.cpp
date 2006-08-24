#include <cstdio>
#include <iostream>
using namespace std;
#define N 1000000
#define MAX 10000
void srnd() {
    srand((unsigned) time(NULL));
}
int main() {
    //ako se linija presjece na 3 random dijela, kolka je vjerojatnost
    // da se moze sloziti trokut
    srnd();
    int k = 0;
    int br = 0;
    for(;k< N;) {
        int a = rand()%MAX, b = rand()%MAX;
        if(a == b) continue;
        if(a > b) swap(a, b);
        int prvi = a, drugi = b-a, treci = MAX-b;
        if(prvi > drugi) swap(prvi, drugi);
        if(drugi > treci) swap(drugi, treci);
        if(prvi+drugi > treci) ++br;
        
        ++k;
    }    
    printf("%lf", (double) br/N/1.000000);
    scanf("\n");
    return 0;
}    
/*max 100
15 46
prvi = 15  = 15
drugi = 46-15 = 31
treci = 100-46 = 54
*/
