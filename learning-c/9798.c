#include <stdio.h>
int main(void) {
  int broj[7],p, i, j, max1, max2, max3, max4, max5, max6;
  max1=0;max2=0;max3=0;max4=0;max5=0;max6=0;
  /*scanf("%s", broj);*/
  for (p = 0; p < 6; ++p)
    scanf("%d",  broj[p]);
  for (p = 0; p < 6; ++p)
    printf("%d ",  broj[p]);
  for (i = 0; i < 6; ++i)
   {
    if (broj[i] > max1)       {
      for (j = 5; j > 0; --j)
        broj[j+1] = broj[j];
      max1 = broj[i];          }
    else if (broj[i] > max2)  {
      for (j = 5; j > 1; --j)
        broj[j+1] = broj[j];
      max2 = broj[i];          }
    else if (broj[i] > max3)  {
      for (j = 5; j > 2; --j)
        broj[j+1] = broj[j];
      max3 = broj[i];          }
    else if (broj[i] > max4)  {
      for (j = 5; j > 3; --j)
        broj[j+1] = broj[j];
      max4 = broj[i];          }
    else if (broj[i] > max5)  {
      for (j = 5; j > 4; --j)
        broj[j+1] = broj[j];
      max5 = broj[i];          }
    else if (broj[i] > max6)  {
      for (j = 5; j > 5; --j)
        broj[j+1] = broj[j];
      max5 = broj[i];          }
   }
  broj[7] = '\0';
  broj[1] = 2; broj[2] = 9;
  printf ("hello\n");
  for (p = 0; p < 6; ++p)
    printf("%d ", broj[p]);
  while (getchar() != 'n')   ;
  return 0;   }
