#include <stdio.h>
#include <stdio.h>
#define fileout "a.txt"
FILE*file;
int main(void) {
  int a[5] = {1, 2, 3, 4, 5};
  int b;
  scanf("%li\n", &b);
  file = fopen(fileout, "w");
  fprintf(file, "%d\n", a[5-b]);
  printf("lol");
  return 0;
}
