#include <stdio.h>
int main(void) {
  char a[10];
  int b = 3;
  scanf("%s", a);
  a[2] = b;
  a[9] = '\n';
  printf("%d", a[2]);
  while (getchar() != 'n')  ;
  return 0;  }
