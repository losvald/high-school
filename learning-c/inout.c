#include <stdio.h>
#define OUTPUT_FILE "inout.out"
#define INPUT_FILE "inout.in"
FILE *file;
int main (void) {
  int a = 1;
  int b = 2;
  file = fopen(INPUT_FILE,"r");
  fscanf (file, "%d %d",&a, &b );
  fclose (file);
  file = fopen(OUTPUT_FILE, "w");
  fprintf (file, "%d", a + b);
  fclose (file);
  return 0; }
