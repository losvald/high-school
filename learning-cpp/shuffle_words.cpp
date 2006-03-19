#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <fstream>
using namespace std;
string str[5000];
void kopiraj(string st, int m) {str[m] = st;}
int main() {
    char gran[] = {' ','.',',','!','?',';',':','(',')','/','-','_',
                   '+','*','@','[',']','\'','\"','&','=','<','>'};
    
    char *podniz, s[10000], c;
    ifstream in("rand teksta.txt", ios::in);
    int k = 0;
    while((c= in.get()) != '|') s[k++] = c;
    s[k] = '\0';
    int m = 0;
    podniz = strtok(s, gran);
    if(podniz) {
        do {
            kopiraj(podniz, m++);
            podniz = strtok(NULL, gran);
        } while(podniz);
    }
    for(int i = 0; i < m; i++) 
        if(str[i].size() > 3) 
            random_shuffle(str[i].begin()+1, str[i].end()-1);
    //for(int i = 0; i < 25; i++) cout << endl;
    for(int i = 0; i < m; i++) cout << str[i] << " ";
    scanf("%d", &m);        
    return 0;
}    
