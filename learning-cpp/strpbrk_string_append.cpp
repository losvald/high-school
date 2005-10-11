#include <cstdio>
#include <cstring>
#include <iostream.h>
#include <ctime>
#include <cstdlib>
using namespace std;
string fun(string str) {
    str.append("lol");
    return str;
}    
int main() {
    string s;
    char s2[1001],s1[1001];
    scanf("%s %s", s1, s2);
    printf("%d", strpbrk(s1, s2));
    
    int temp;
    scanf("%d", &temp);
    return 0;
}    
