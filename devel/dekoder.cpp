#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include <vector.h>
#include <algorithm>
#include <conio.h>
#include <fstream.h>
#include <ctype.h>
#include <numeric>
using namespace std;
int main() {
   const bool da = true;
   char c, str[1000], *podniz;
   int i = 0;
   string temp;
   vector<string> niz;
   ifstream in ("in.txt", ios::in);
   ofstream out("out.txt", ios::in); 
   while(da) {
       c = in.get();
       if(c == '!') break;
       else if(isalnum(c))
         str[i++] = c;
   }
   str[i] = '\0';    
   podniz = strtok(str, " ");
   if(podniz) {
       do {
           niz.push_back(podniz);
           podniz = strtok(NULL, " ");
       } while(podniz);
   }
   vector<string> v2(niz.size()); 
   reverse_copy(niz.begin(), niz.end(), v2.begin());
   //sort(v2.begin(), v2.end());
   //vector<string>::iterator newend = unique(v2.begin(), v2.end());
   //v2.erase(newend, v2.end());
   //niz.clear();
   vector<string> s(1, "leden_os");
   vector<string>::iterator it;
   it = find_first_of(v2.begin(), v2.end(), s.begin(), s.end());
   v2.erase(it, v2.end());
   niz.clear();
   niz = v2;           
   for(vector<string>::iterator iter = niz.begin(); iter != niz.end(); iter++)
     cout << *iter;
   cout << niz.front();  
   getch();
   return 0;
}       
