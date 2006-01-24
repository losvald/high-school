#include <cstdio>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <vector.h>
#define MAX 100000000
FILE *file;
bool a[MAX];
int main() {
    file = fopen("andrej_pr.txt", "w");
    float vr = clock(); vector<long int> v;
    for(int i=2; i*i <= MAX; i++) {
        for(int j = 2; j*i <= MAX; j++)
          if(!a[i*j]) a[i*j] = true; 
    }
    long int br = 0;
    for(int i = 2; i <= MAX; i++) {
      if(!a[i]) br++;
      if(!(i % 10000)) {v.push_back(br);fprintf(file, "\n%6ld%10ld", i, br);}
    }
    vector<long int> v2(v.size()); 
    adjacent_difference(v.begin(), v.end(), v2.begin());
    fprintf(file, "\n\nRazlike:\n");
    for(int i = 0; i < v2.size(); i++)
     fprintf(file, "\n%6ld%10ld", (i+1)*10000, v2[i]);
    fprintf(file,"%ld (%.2lf ms)", br, (clock()-vr));
    fclose(file);   
    return 0;
}    
