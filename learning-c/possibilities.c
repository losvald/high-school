#include <stdio.h>
int main(void) {
  int a[100];
  int j, m, n, i, p,k, buffer, assign, value;
  scanf("%d", &m);
  n = m * m;
  k = 1;
  for (assign = 0, value = 1; assign < n; assign++, value++)
    a[assign] = value;
  for (i = 0; i < m; i++) {
    for (j = 1; j < m; j++, k++) {
      buffer = a[j];
      a[j] = a[0];
      a[0] = buffer;
      printf("%d. ", k);
      for (p = 0; p < m; p++)
        printf("%d,", a[p]);
      printf("\n");
      }
  }
  while (getchar() != 'n')  ;
}

