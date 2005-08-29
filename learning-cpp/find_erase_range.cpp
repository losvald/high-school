#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <vector.h>
#include <ctype.h>
#include <algorithm>
#include <functional>
int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v(a, a+10), v2(a+3, a+6);
    for(int i = 0; i < v2.size(); i++) 
      cout << v2[i] << " ";
    reverse(v2.begin(), v2.end());
    pair<vector<int>::iterator, vector<int>::iterator> par;
    par.first = find(v.begin(), v.end(), v[3]);
    par.second = find(v.begin(), v.end(), 7);
    v.erase(par.first, par.second);
    v.insert(par.first, v2.begin(), v2.end());
    
    cout << endl;
    for(int i = 0; i < v2.size(); i++) 
      cout << v2[i] << " ";
    
    for(int i = 0; i < 10; i++) cout << v[i] << " ";
    getch();
}    
