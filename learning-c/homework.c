#include <stdio.h>
int main(void)
{
  int broj, i, a, mod;
  int B[2];

  scanf("%d", &broj);

  a = broj/2;
  mod = a % 4;
  if (mod == 0) {
     B[0] = a + 1; B[1] = a + 1 + mod;
     }

  printf("%s", B);
  while (getchar() != 'n') ;
  return 0;
}
    
