#include <stdio.h>
int main(void) {
  int a[6], i;
  char b2[6], b[5] = "1938\0";

  sprintf(b2, "%d", b);
  printf("\novo je %s", b2);
  /*for(i= 0; i < 7; i++)
  printf("\%d", a);  */
  while (getchar() != 'n');
  return 0;
}


