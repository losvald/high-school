#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXLINE 1000
int check(char letter2[], char ch);
long int roni(long int b3, int factor2);
int main (void)
{
  char ch, f, letter[26], niz[MAXLINE];
  int i, g, h, factor;
  long int b;
  int random = 7;
  
  printf("Upisite 1-5 za nacin desifriranja!");
  scanf("%d", &factor);
  printf("Dobar dan! Dobrodosli u prodavaonicu oruzja!\n");
  printf("Napisite ime oruzja i dobit cete njegovu sifru!");
  printf("\nSada upisite ime:\n");
  for (f = 'A', g = 0; f <= 'Z'; f++, g++)
    letter[g] = f;
  if (getchar() == '\n');
  {
  for(i = 0; (ch = getchar()) != EOF && ch != '\n'; ++i) {
    if (ch >= 'A' && ch <= 'Z')    {
      b = check(letter, ch);
      b = roni(b, factor);
    if (b == 0)
      niz[i] = 'Q';
    else {
      if (b > 26) {
        b = b % 26;
        if (b == 0)
          b = 26;
      }
      niz[i] = letter[b-1];
    }  }
    else
      niz[i] = ' ';
  }
  }
  niz[i] = '\0';
  printf("%s", niz);
  printf("\nDobili ste sifru, zalim, vise ne mozete narucivati!");
  while (getchar() != 'N') ;
  return 0;
}

int check (char letter2[], char ch2)
{
  int j;
  
  for (j = 0; j < 26; j++)  {
    if (letter2[j] == ch2) {
      return j+1;
      break;
    }
  }
}
long int roni(long int b3, int factor2)
{
  double broj = 9876.54321;
  double result3;
  long int result_final;
  result3 = broj * sqrt(b3) * factor2;
  result3 *= 1000;
  result_final = result3/b3;

  return result_final;
}
