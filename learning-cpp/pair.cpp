#include <conio.h>
#include <iostream.h>
#include <vector.h>
#include <algorithm>
#include <stdio.h>
int main() {
    int a[6] = {1, 4, 6, 7, 10, 25};
    vector<int> v2(&a[0], &a[5]);
    pair<vector<int>::iterator, vector<int>::iterator> par;
    par.first = lower_bound(v2.begin(), v2.end(), 7);
    par.second = upper_bound(v2.begin(), v2.end(), 4);
    cout << *par.first << " " << *par.second;
    getch();
    return 0;
}    
