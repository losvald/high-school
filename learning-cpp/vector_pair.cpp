#include <stdio.h>
#include <algorithm>
#include <conio.h>
#include <numeric>
#include <string.h>
#include <vector.h>
#include <iostream.h>
using namespace std;
int main() {
    vector< pair<int, int> > v;
    v.resize(3);

    for(int i = 0; i < v.size(); i++) cout << v[i].first << " " << v[i].second << endl;
    getch();
    return 0;
}    
