#include <vector.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    vector<char> niz;
    size_t ind;
    string deno("kaj radis");
    char br[8] = {'1','2','3','4','5','6','7','8'};
    for(int i = 0; i < 7; i++) {
        niz.push_back(br[i]);
    }
    //ind = niz.find('3');
    niz.clear();
    niz.insert(niz.begin(),deno.begin(), deno.end());
    reverse(niz.begin(), niz.end());
    sort(niz.begin(), niz.end());
    for(int i = 0; i < niz.size(); i++) 
      cout << niz[i] << " ";  
    getch();
    return 0;
}        
