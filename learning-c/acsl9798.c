#include <stdio.h>
int main (void) {
  int  i, j, p, buffer;
  char a[6];
    scanf("%s", a);
  for (i = 0; i < 5; ++i) {
    for (j = i+1; j < 6; ++j) {
      if (a[j] > a[i]) {
      buffer = a[i];
      a[i] = a[j];
      a[j] = buffer; }
    }
  }
  for (p = 0; p < 6; ++p)
    printf("%c", a[p]);
  while (getchar() != 'q')  ;
return 0; }
