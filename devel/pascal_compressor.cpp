#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;
int main() {//Complexity: O(number of characters in the program)
  string s = "}", ret;
  FILE *in = fopen("in.txt", "r");
  for(static char buff[1000000]; fscanf(in, "%s", &buff) > 0; )
    s += string(isalpha(s[s.size()-1]) && isalpha(buff[0]) ? " ": "") + buff;
  s += "{";
  for(int a, b = -1; (a = s.find("}", b+1)) != string::npos; )
    ret += s.substr(a+1, (b = s.find("{", b+1)) - a - 1);
  FILE *out = fopen("out.txt", "w");
  fprintf(out, "%s", ret.c_str());
  return 0;
}
