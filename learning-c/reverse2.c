#include <stdio.h>
#define MAXLINE 1000
#define INPUT_FILE "reversein.txt"
#define OUTPUT_FILE "reverseout.txt"
FILE *file;

char reverse(char s[], int j);

int main(void) {
  char line[MAXLINE];
  char c;
  int j, i;
  file = fopen(INPUT_FILE, "r");
  for (i=0;(c = fscanf(file, "%i")) != EOF && c!='\n'; ++i)
    line[i] = c;
  line[i] = '\0';
  reverse(line, i);
  fclose(file);
  file = fopen(OUTPUT_FILE, "w");
  fprintf(file,"\n%s", line);
  fclose(file);
  for (j = 0; j < i; ++j)
  printf("%c", line[j]);
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
  
  
