#include <stdio.h>
void swap(int *pa, int *pb);
int main(void) {
  int a, b;
  printf ("Napisite broj a i b (sa raymakom odvojite)!");
  scanf ("%d %d", &a, &b);
  swap(&a,&b);
  printf ("Obrnut redoslijed je %d %d", a, b);
  while (getchar() != '0')
     ;
  return 0;
}
void swap (int *pa, int *pb) {
  int temp;
  temp = *pa;
  *pa = *pb;
  *pb = temp;
}
