#include <vector.h>
#include <iostream.h>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>

#define MAX 10000
int main() {
    vector<long long double> v1(MAX);
    for(long int i = 1; i <= MAX; i++)
      v1.push_back(i);
    random_shuffle(v1.begin(), v1.end());
    getch();
    cout << "Pocinje...";
    sort(v1.begin(), v1.end());
    cout << "Zavrseno!";
    random_shuffle(v1.begin(), v1.end());
    getch();
    cout << endl << "sada pocinje rucno slaganje...";
    for(int i = 0; i < MAX-1; i++) {
        for(int j = i+1; j < MAX; j++) {
            if(j < i) {
                int t = v1[j];
                v1[j] = v1[i];
                v1[i] = t;
            }
        }
    }
    cout << "zavrseno!";
    getch();
    return 0;
}                  
    
