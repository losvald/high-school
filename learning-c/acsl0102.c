#include <stdio.h>
int check(char letter2[], char ch);
int main (void)
{
  char ch, f, letter[26];
  int i, g,h, b;

  for (f = 'A', g = 0; f <= 'Z'; f++, g++)
    letter[g] = f;
  for(i = 1; i <= 5; i++) {
    scanf("%c", &ch);
    if (ch >= 'A' && ch <= 'E')
      b = check(letter, ch) * 2;
    else if (ch >= 'F' && ch <= 'J')
      b = (check(letter, ch) % 3) * 5;
    else if (ch >= 'K' && ch <= 'O')
      b = (check(letter, ch) / 4) * 8;
    else if (ch >= 'P' && ch <= 'T') {
      b = check(letter, ch);
      if (b >= 10 && b < 20)
        b = (b % 10 + 10/10) * 10;
      else
        b = (b % 20 + 20/10) * 10;
    }
    else if (ch >= 'U' && ch <= 'Z') {
      b = check(letter, ch);
      for (h = b - 1; h >= 1; h--) {
        if (b % h == 0) {
          b = h * 12;
          break;
        }
      }
    }
    if (b <= 26 && b == 0)
      printf("\n%d. #", i);
    else {
      if (b > 26) {
        b = b % 26;
        if (b == 0)
          b = 26;
      }
      printf("\n%d. %c", i, letter[b-1]);
    }
  }
  while (getchar() != 'n') ;
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
