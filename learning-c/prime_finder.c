#include <stdio.h>
int main(void) {
  long int min, max, a[10000], a2, j, i;
  a[0] = 2; a[1] = 3; a2 = a[1];
  printf("Napisite broj OD kojeg zelite da se ispisu svi prosti brojevi\n");
  printf(" i broj DO kojeg zelite da se ispisu prosti brojevi!\n");
  scanf("%li %li", &min, &max);
  for (i = min; i <= max; ++i) {
    for(j = 0 ; ((i % a[j]) != 0 && a[j] != a2); ++j)
    if ((i % a[j-1]) != 0) {
      a[j] = i;
      a2 = i;
      printf("%li\n", a[j]);        }
  }

  return 0; }





