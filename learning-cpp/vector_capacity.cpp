#include <stdio.h>
#include <conio.h>
#include <vector.h>
#include <iostream.h>
int main() {
    int c;
    vector<int> v2;
    //v2.reserve(100);
    for(int i = 0; i < 100; i++) {
        c = v2.capacity();
        v2.push_back(i);
        if(c != v2.capacity()) 
            cout << "v2 grown from " << c << "to " << v2.capacity() << endl;
    }
    getch();
    return 0;
}        
