#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
using namespace std;
int t[50], br = 0;
int kartice[18] = {13,26,29,34,50,53,94,91,103,112,117,132,138,141,155,174,197,198};
int rnd(int raspon)
{
  int r, j;
  ponovi:
   r=rand()%raspon;
   for(j = 0; j <= 10; j++) {
     if(r == t[j])
       goto ponovi;
   }
   t[br++] = r;
   return r;
}
void srnd(void)
{
  srand((unsigned) time(NULL));
}
int main() {
    int i, j;
    srnd();
    for(i= 0; i < 60; i++) {
      getchar();
      cout << kartice[rnd(18)];
      cout.flush();
      double t = clock();
      while ((clock() - t) < CLOCKS_PER_SEC)
        ;
      cout << "\b\b\b" << "   ";
  }

    scanf("\n");
    return 0;
}
