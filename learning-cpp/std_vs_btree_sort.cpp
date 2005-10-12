#include <stdio.h>
#include <conio.h>
#include <vector.h>
#include <algorithm>
#include <iostream.h>
#define max 32768
#define NAJ 300
using namespace std;
int polje[1000000];
vector<int> v1(1000000);
void print(int node) {
    if(polje[node*2+1] != -1)
      print(node*2+1);
    printf("%d", polje[node]);
    if(polje[node*2+2] != -1)
      print(node*2+2);
}      
int main() {
    int n; int node, a;
    for(long i = 0; i < 99999; i++) {
      polje[i] = -1;
      if(i < NAJ)
        v1[i] = i;
    }
    v1.resize(NAJ);
    random_shuffle(v1.begin(), v1.end());   
    //scanf("%d", &n);
    //scanf("%d", &polje[0]);
    polje[0] = v1[0];
    for(int j = 1; j < NAJ; j++) {
        //scanf("%d", &a);
        a = v1[j];
        node = 0;
        while(polje[node] != -1) {
            if(a <= polje[node])
              node=node*2+1;
            else
              node=node*2+2;
        }    
        polje[node] = a; 
    }
    
    printf("\nPritisnite za pocetak!\n");
    getch(); 
    print(0);
    printf("\nZavrseno!!! Pritisnite za pocetak!\n");
    getch();
    sort(v1.begin(), v1.end());
    for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
      printf("%d", *iter);
    printf("\nGotovo!!!!!!!");
    getch();
    return 0;
}    
              
