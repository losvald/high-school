#include <string.h>
#include <vector.h>
#include <algorithm>
#include <conio.h>
#include <iostream.h>
#include <deque.h>
#include <functional>
using namespace std;
void ispisi() {
    int niz[10] = {6,15,24,2,56,198,32,65,39,10};
    deque<int> skup(niz, niz+10);
    deque<int> skup2;
    sort(skup.begin(), skup.end());
    for(int i = 0; i < skup.size(); i++)
      cout << skup[i] << " ";
    cout << endl << "********" << endl;
    skup2.push_back(-1); skup2.push_back(2000);
    deque<int> mergedresults(skup.size()+skup2.size());
    merge(skup.begin(), skup.end(), skup2.begin(), skup2.end(),mergedresults.begin());
    cout << "[[" << mergedresults.size() << "]]" << endl;
    for(deque<int>::iterator iter = mergedresults.begin(); 
        iter != mergedresults.end(); iter++)
        cout << *iter << " ";
    cout << endl;
    count_if(skup.begin(), skup.end(), bind2nd(equal_to<int>(), 10));    
    
}    
int main() {
    char c; int i;
    char *podniz;
    char str[80];
    vector<string> niz;
    for(i = 0;(c = getchar()) != EOF && c != '\n'; i++)
      str[i] = c;
    str[i] = '\0';  
    podniz = strtok(str, " ");  
    if(podniz) {
        do {
            niz.push_back(podniz);
            podniz = strtok(NULL, " ");
        } while(podniz);
    }
    sort(niz.begin(), niz.end());
    vector<string>::iterator dupl;
    dupl = unique(niz.begin(), niz.end());
    niz.erase(dupl, niz.end());
    for(vector<string>::iterator iter = niz.begin(); iter != niz.end(); iter++) 
        cout << *iter << endl;
    ispisi();    
    getch();
    return 0;
}               
       
