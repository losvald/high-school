#include <stdio.h>

int main(void) {
  long long a[30000] = {1 - 30000};
  long long c;
  scanf("%Li\n", &c);
  a[c] = c;
  printf ("%Li", a[c]);
  return 0;
  }
  
