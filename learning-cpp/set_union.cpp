#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
int main() {
    string s, s1("abcde"), s2("cdmno");
    char str[100]; int a[] = {1, 2, 4, 6, 7, 8}; int b[] = {2, 4, 9, 10, 12, 13};
    vector<int> v, v1(a, a+6), v2(b, b+6);
    v.resize(v1.size()+v2.size());
    vector<int>::iterator iter = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
    v.erase(iter, v.end());
    for(iter = v.begin(); iter != v.end(); iter++) printf("%d ", *iter);
    
    scanf("%s", str);
    
    return 0; 
    
    
}    
