#include <stdio.h>
#include <math.h>
int main(void) {
  int a;
  a = rand(7);
  printf("%d", a);
  while (getchar() != 'n') ;
  return 0;
}

