#include <cstdio>
#include <ctime>
using namespace std;
int n, mat[100][100], mat2[100][100], sol, m;
int main() {
    printf("Upisi broj redaka tj. stupaca: "); scanf("%d", &n);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j) scanf("%d", &mat[i][j]);
    double start = clock();
    printf("Upisi rjesenje: "); scanf("%d", &m);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; sol+=mat2[i][j++])
        for(int k = 0; k < n; ++k) mat2[i][j] += mat[i][k]*mat[k][j];
    for(int i = 0; i < n; ++i, printf("\n"))
      for(int j = 0; j < n; ++j) printf("%3d", mat2[i][j]); 
    if(sol == m) printf("Pogodio si");
    else printf("Krivo (%d). Trebalo ti je %d s", sol, int((clock()-start)/1000));
    scanf("\n");
    return 0;
}    
