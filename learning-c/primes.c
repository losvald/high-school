#include <stdio.h>
int main(void) {
  long int a[100000], i, j, max, p, g, h, t;
  long int l = 0;
  long long int ne, broj, J;
  scanf("%li", &max);
  if (max >= 2) {
    l = 2;
    printf("1\t2\t"); }
  else if (max >= 1) {
    l = 1;
    printf("1\t"); }
  /*for (t = 0; t < max; t++)
    a[t] = 2; */
  for (i = 1; i <= max; i++) {
    if (a[i] != 2) {
    for (j = 2; j < i && h < i; j++) {
      if (i % j == 0) {
        h = i;
        for (g = 1; g*(i-1) <= max && i > 1; g++)
          a[g*(i-1)] = 2;                }
      else if (i % j != 0 && j == (i-1))  {
        printf("%li\t", i);
        l += 1;
        a[i-1] = 1;    } }
    }
  }
/*  for (p = 0; p < max; p++) {
    if (a[p] == 1)
      printf("%d ", p);   }  */
  printf("\nDo broja kojeg ste ukucali ima %li prostih brojeva!", l);
  while (getchar() != 'q') {
  ne = 0;
  printf("\nSada napisite za koji broj zelite provjeriti da li je");
  printf(" prost ili nije! Ako ne yelite pritisnite q!");
  scanf("%Li", &broj);
  if (broj == 2) printf("Broj 2 je prost broj!");
  else if (broj == 2) printf ("Broj 2 je prost broj!");
  else {
  for(j = 2; j < broj; ++j) {
    if (broj % j == 0)
      break;
    else if(broj % J != 0 && j == (broj-1))   {
      printf ("Broj %Li je prost broj!", broj);
      ne = 1; }
   }
   }
  if (ne == 0) printf("Broj %Li nije prost broj!", broj);
  }
  printf("Za izlaz iz programa pritisnite n!");
  while (getchar() != 'n')
  ;
  return 0;
}




