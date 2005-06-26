#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <vector.h>
#include <algorithm>
int main() {
    int a[5] = {5,6,7,10,2};
    int b[5] = {6, 7, 11, 8, 1};
    vector<int> A(a, a+5);
    vector<int> B(b, b+5);
    vector<int> C(20);
    set_difference(A.begin(), A.end(), B.begin(), B.end(), C.begin());
    for(vector<int>::iterator iter = C.begin(); iter != C.end(); iter++) 
        cout << *iter << " ";
    vector<int> d;
    cout << endl;
    d.insert(d.end(), A.begin(), A.end());
    d.insert(d.end(), B.begin(), B.end());
    for(vector<int>::iterator iter = d.begin(); iter != d.end(); iter++) 
        cout << *iter << " ";
    getch();
    return 0;
}    
    
