#include <stdio.h>
#include <string.h>
int razmak(char* , int);
int main(void) {
  char rijec[21], a, c;
  printf ("Napisite recenicu da zauzima 20 mjesta!\n");
  for (i=0; i < 21; ++i;) {
    c = getchar();
    rijec[i] = putchar (c);
    }
  rijec[21] = '\0';
  printf ("Sada napisite iza kojeg zelite ubaciti razmak!");
  scanf ("%d", &a);
  razmak(rijec, a);
  strcpy (rijec, rijec);
  printf ("Evo ga: %s", rijec);
  }

int razmak(char *p, int x) {
  int j;
  char *z;
  z = *(rijec + 20);
  for (j = 20; j > x; j++) {
    *p = *--p;
    p = p + 2;
    }
  *p = ' ';
  return 0;
}

