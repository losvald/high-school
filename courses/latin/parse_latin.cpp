#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <vector.h>
#include <algorithm>
#include <ctype.h>
#include <string.h>
using namespace std;
int main() {
    vector<string> v1;
    vector<string>::iterator un, iter;
    char c, str[10000], *podniz; int k = 0;
    ifstream in("latin.txt", ios::in);
    ofstream out("latout.txt", ios::out);
    while((c = in.get()) != '&') {
        if(c != '\n') {
          str[k++] = c; cout << c;}
    }
    str[k] = '\0';
    podniz = strtok(str, " ");
    if(podniz) {
        do {
            v1.push_back(podniz);
            podniz = strtok(NULL, " ");
        } while(podniz);
    }
    sort(v1.begin(), v1.end());
    un = unique(v1.begin(), v1.end());
    v1.erase(un, v1.end());
    for(iter = v1.begin(); iter != v1.end(); iter++)
      out << *iter << endl;
    getch();
    return 0;
}                
