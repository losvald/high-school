#include <stdio.h>
#include <math.h>
int zbroj(int x);
int provjera(int b[], int M, int N, int RES);
int main(void) {
  int a[100];
  int j, m, n, i, p, buffer, assign, value, res, ajde;
  int printed = 0;

  scanf("%d", &m);
  n = m * m;
  for (assign = 0, value = 1; assign < n; assign++, value++)
    a[assign] = value;
  res = zbroj(n);

  printf("Ajde!");
  scanf("%d", &ajde);
  if (ajde == 1) {
    a[0]=12;a[1]=6;a[2]=15;a[3]=1;a[4]=13;a[5]=3;a[6]=10;a[7]=8;a[8]=2;
    a[9]=16;a[10]=5;a[11]=11;a[12]=7;a[13]=9;a[14]=4;a[15]=14;
    n = 16; m = 4; res = 34;
    provjera(a, m, n, res); }
  else
  {
  for (i = 0; i < m && printed != 1; i++) {
    for (j = 1; j < m; j++) {
      buffer = a[j];
      a[j] = a[0];
      a[0] = buffer;
      printed = provjera(a, m, n, res);
      if (printed == 1)
        break;
    }
  }
 }
  while (getchar() != 'n')  ;
}
int zbroj(int x) {
  int y;
  int z = 0;
  for (y = x; y > 0; y--)
    z += y;
  return z/(sqrt(x));
}
int provjera(int b[], int M, int N, int RES) {
  int g, c, h;
  int no = 0;
  int check = 1;
  while (check != 2)
  {
  printf("MOyda radi");
  for (g = 0; g < M; g++) {
    c = 0;
    for (h = g; h <= N; h += M)
      c += b[h];
    if (c != RES) {
      check = 2;
      break; }
    else if (g == M-1)
      check = 1;
  }
  if (check == 2) break;
  c = 0;
  for (h = 0; h <= N; h += M+1)
      c += b[h];
    if (c != N) {
      check = 2;
      break;     }
    else if (h = N + M)
      check = 1;
  if (check == 2) break;
  c = 0;
  for (h = M-1; h < N-1; h += M-1)
    c += b[h];
  if (c != RES)  {
    check = 2;
    break;      }
  else
    check = 1;
  for (g = 0; g <= N-M; g += M) {
    c = 0;
    for (h = 0; h < M; h++)
      c += b[g+h];
    if (c != RES) {
      check = 2;
      break;     }
    else if (g == N-M)
      check = 1;  printf("Radi!!!!");
  }
  if (check == 1) {
    no = 1;
    printf("\n");
    for (g = 0; g <= N-M; g+= M) {
      for (h = 0; h < M; h++)
        printf("%d\t", b[g+h]);
      printf("\n");
    }
  }
  check = 2;
  }
  if (no == 1)
    return 1;
  else
    return 0;
}
