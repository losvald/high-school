#include <stdio.h>
int main (void) {
  int a[6], i, j, p, buffer;
    scanf("\n%d", &a[0]);
    scanf("%d", &a[1]);
    scanf("%d", &a[2]);
    scanf("%d", &a[3]);
    scanf("%d", &a[4]);
    scanf("%d", &a[5]);
  for (i = 0; i < 5; ++i) {
    for (j = i+1; j < 6; ++j) {
      if (a[j] > a[i]) {
      buffer = a[i];
      a[i] = a[j];
      a[j] = buffer; }
    }
  }
  for (p = 0; p < 6; ++p)
    printf("%d ", a[p]);
  while (getchar() != 'q')  ;
return 0; }
