#include <stdio.h>
#include <ctype.h>
#include <math.h>
int check(char ln, char hex2[]);
int main(void)
{
  char c, line[1000], hex[16];
  int i, f, g, m;
  long int res;

  for (f = 'A', g = 9; f <= 'F'; f++, g++)
    hex[g] = f;
  for (i = 0; (c = getchar()) && c != '\n' && ( isdigit(c)
        || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f') ; i++)
  {
    if (c >= 'a' && c <= 'f')
      c += 'A' - 'a';
    line[i] = c;
  }
  line[i] = '\0';
  i--;
  res = 0;
  for (m = 0; i >= 0; m++, i--)
    res += check(line[i], hex) * pow(16, m);
  printf("%d", res);
  while (getchar() != 'n') ;
  return 0;
}
int check(char ln, char hex2[])
{
  int l;

  for (l = 0; l < 16; l++) {
    if (ln == hex2[l])
      return l+1;
  }
}
