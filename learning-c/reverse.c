#include <stdio.h>
#define MAXLINE 1000

char reverse(char s[], int j);

int main(void) {
  char line[MAXLINE];
  char c, i;
  printf("Napisite tekst koji zelite da se napise obrnuto:\n");
  for (i=0;(c = getchar()) != EOF && c!='\n'; ++i)
    line[i] = c;
  line[i] = '\0';
  reverse(line, i);
  printf("**********************");
  printf("\n%s", line);
  printf("\nPritisnite n ya izlaz!");
  while (getchar() != 'n')
  ;
  return 0;  
}
char reverse(char s[], int j) {
  int k, buffer;
  --j;
  for (k = 0; k < j && j >= 0; ++k, --j) {
    buffer = s[j];
    s[j] = s[k];
    s[k] = buffer;
  }
}
  
  
