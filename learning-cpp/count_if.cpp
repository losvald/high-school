#include <algorithm>
#include <stdio.h>
#include <functional>
#include <iostream>
#include <vector.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <deque.h>
#include <set.h>
#include <assert.h>
#include <iomanip.h>
#include <numeric>
#include <math.h>
#include <ctype.h>
#include <fstream.h>
#include <time.h>
#include <locale.h>
using namespace std;
bool leo(int i) {
    return (i <= 15 && i >= 4);
}     
int main() {
    int br = 0;
    int n[8] = {1,3,6,8,15,20,35,40};
    vector<int> v1(n, n+8);
    vector<int>::iterator iter;
    br = count_if(v1.begin(), v1.end(), leo);
    cout << br << endl;
    cout << count_if(v1.begin(), v1.end(), bind2nd(greater_equal<int>(), 15));  
    //v1.remove_if(v1.begin(), v1.end(), 
    getch();
    return 0;
}    
