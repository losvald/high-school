int zbroj(int x);
int main2(int N, int M, int RES);
  int k = 1;
  int b[16] = {1,2, 3, 4,
               5, 6,7, 8,
               9, 10, 11, 12,
               13,  14, 15, 16  };
int main(void) {
  int res, n, m, buffer, j, i;
  int a[16] = {12,6, 15, 1,
               13, 3,10, 8,
               2, 16, 5, 11,
               7,  9, 4, 14  };

  scanf ("%d", &m);
  n = m*m;
  res = zbroj(n);
  for (i = 0; i < n; i++) {
    for (j = 1; j < n; j++, k++) {
      buffer = b[j];
      b[j] = b[0];
      b[0] = buffer;
      main2(n, m, res);     }}
  while (getchar() != 'n') ;
  return 0;
}
int main2(int N, int M, int RES) {
  int g, c, h, t, check;
  printf("\n");
  printf("%d. ", k);
  for (g = 0; g < N; g++)
        printf("%d,", b[g]);
  printf("\t");
  check = 1;
  while (check != 2)
  {
  for (g = 0; g < M; g++) {
    c = 0;
    for (h = g; h <= N; h += M)
      c += b[h];
    if (c != RES) {
      check = 2;  printf("s(%d) ", c);
      break; }
    else if (g == M-1)           {
      check = 1;
      printf("\nBingo u stupcima%d!!!\n", g);  }
  }
  /*if (check == 2) break;*/
  c = 0;
  for (h = 0; h <= N; h += M+1)
      c += b[h];
    if (c != RES) {
      check = 2;  printf("u1(%d) ", c);
      break;     }
    else if (h = N + M)        {
      check = 1;
      printf("Bingo ukoso1(%d!!!", h);  }
  /*if (check == 2) break; */
  c = 0;
  for (h = M-1; h < N-1; h += M-1)
    c += b[h];
  if (c != RES)  {
    check = 2;   printf("u2(%d) ");
    break;      }
  else      {
    check = 1;
    printf("Bingo ukoso2!!!");  }
  for (g = 0; g <= N-M; g += M) {
    c = 0;
    for (h = 0; h < M; h++)
      c += b[g+h];
    if (c != RES) {
      check = 2;   printf("r(%d)", c);
      break;     }
    else if (g == N-M)  {
      check = 1;
      printf("\nBingo u redovima%d!!!", g); }
  }
  if (check == 1) {
    printf ("Bravooooooo!");
    printf("\n");
    for (g = 0; g <= N-M; g+= M) {
      for (h = 0; h < M; h++)
        printf("%d\t", b[g+h]);
      printf("\n");    }
  }
  check = 2;
  }
  return 0;   }
  
int zbroj(int x) {
  int y;
  int z = 0;
  for (y = x; y > 0; y--)
    z += y;
  return z/(sqrt(x));
}  
