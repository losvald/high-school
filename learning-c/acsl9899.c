#include <stdio.h>
#include <math.h>
int factorial(int faktorijelaBroja);
int main(void) {                /* Glavna funkcija*/
  int N, k, i;
  float p, suma;
  for (i = 1; i < 6; ++i) {
    printf("Line #%d: ", i);
    scanf("%d %d %f", &N, &k, &p);
    suma = ( factorial(N)/( (factorial(N-k)) * (factorial(k)) ) )
           * pow(p, k) * pow( (1-p), (N-k) );
    printf("Output #%d: %g\n", i, suma); }
  return 0;
}
int factorial(int m) {       /*Izracunati faktorijelu*/
  int result;
  if (m == 0 || m == 1)
    result = 1;
  else {
    result = m;
    while (m > 1)
      result *= --m; }
  return result; }
