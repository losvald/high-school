#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
FILE *in, *out;
vector<string> v;
char buff[50];
int main() {
  in = fopen("all_words.txt", "r");
  out = fopen("all_words_sorted.txt", "w");
  v.reserve(600000);
  while( fgets(buff, 49, in) )
    v.push_back(buff);
  sort(v.begin(), v.end());
  v.erase( unique(v.begin(), v.end()), v.end() );
  for(int i = 0; i < v.size(); ++i)
    fprintf(out, "%s", v[i].c_str());
  printf("done");
  scanf("\n");
  return 0;
}
