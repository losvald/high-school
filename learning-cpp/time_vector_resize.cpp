#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
//int polje[5000000];
vector<int> v;
list<int> l;
int main() {
    int max; double start;
    scanf("%d", &max);
     start = clock();
     v.resize(max);
    for(int i = 0; i < max; i++) v[i] = i;
    printf("\n%lf ms.", clock()-start);
    scanf("%d", &max);
    return 0;
}    
