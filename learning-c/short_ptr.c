#include <stdio.h>

short b;

short leo(short *p);

int main(void) {
  short a[5] = {10, 20, 30, 40, 50};
  short f;
  printf ("\nHello! napisite koji po redu");
  printf (" element hocete da ispise (1-5)!\n");
  scanf ("%hi", &b);
  printf ("\nNapisali ste %hi", leo(a));
  scanf;
}
short leo (short *p) {
  short d ;
  for (; (b>6 && b>0); b--)
    d = *++p;
  return d;
}
