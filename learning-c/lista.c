#include <stdio.h>
#define van "lista.txt"
#define unutra "lista2.txt"
FILE *fajl, *fajl2;
int main(void) {
  long a[30000] = {1 - 30000};
  long N, M, X, Y, buffer, i;
  fajl = fopen(van, "w");
  fajl2 = fopen(unutra, "r");
  fscanf(fajl2, "%li %li", &N, &M);
  for (i = 1; i <= M; i++) {
    fscanf(fajl2, "%li %li", &X, &Y);
    if (X == N && Y == 'D')
      ;
    else if (X == 1 && Y == 'G') {
      buffer = a[0];
      a[0] = a[N-1];
      a[N-1] = buffer; }
    else if (Y == 'G') {
      buffer = a[X-1];
      a[X-1] = a[X];
      a[X] = buffer;   }
    else if (Y == 'D') {
      buffer = a[X-1];
      a[X-1] = a[X-2];
      a[X-2] = buffer; }
  }
  fprintf(fajl, "\n%li\n", a[0]);
  fclose (fajl);
  fclose (fajl2);
}

