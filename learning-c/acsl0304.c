#include <stdio.h>
int check (char pravi2[], char skup2[]);
int dcheck (char result3);
int main(void)
{
  char skup[7], pravi[7], buffer, result2;
  int i, j, l, result;

  scanf("%s", skup);
  for (l = 0; skup[l] != '\0'; l++)
    pravi[l] = skup[l];
  pravi[l] = '\0';
  printf("(pravi = %s)\n", pravi);
  for (i = 0; i < 5; i++) {
    for (j = i + 1; j < 6; j++) {
      if (skup[j] > skup[i]) {
      buffer = skup[i];
      skup[i] = skup[j];
      skup[j] = buffer; }
    }
  }
  printf("%s", skup);
  if (skup[0] % 2 != 0)
    pravi[check(pravi, skup)] = '0';
  else {
    result2 = pravi[check(pravi, skup)];
    printf("\npravi[check] = %c\n", result2);
    result = dcheck(result2) + 4;
    printf("\nresult = %d\n", result);
    if (result >= 10)
      result %= 10;
    pravi[check(pravi, skup)] = result - '0';
    printf("\n pravi[check] je sada %c\n", pravi[check(pravi, skup)]);
  }
  for (j = 0; pravi[j] == '0'; j++) {
    for (i = 0; i < 9; i++) {
      printf("\thehe\t");
      pravi[i] = pravi[i+1];
      printf("%d", i);   }
  }

  printf("\n%s", pravi);
  while (getchar() != 'n')  ;
  return 0;
}
int check (char pravi2[], char skup2[])
{
  int g;
  
  for (g = 0; g < 7; g++) {
    if (pravi2[g] == skup2[0]) {
      return g;
      break;   }
  }
}
int dcheck(char result3)
{
  char dig[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int g;

  for (g = 0; g <= 10; g++) {
    if (result3 == dig[g]) {
      return g;
      break;  }
  }
}


