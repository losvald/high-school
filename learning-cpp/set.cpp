#include <iostream.h>
#include <set.h>
#include <string.h>
#include <conio.h>
using namespace std;
int main() {
    set<string> ravnice;
    string ime;
    ravnice.insert("Fico");
    ravnice.insert("Viki");
    ravnice.insert("Ennio");
    ravnice.insert("Joso");
    cout << "Upisite svoje ime: ";
    cin >> ime;
    set<string>::iterator leo = ravnice.find(ime);
    if(leo != ravnice.end())
      cout << "Vi ste a ravnicama!";
    else
      cout << "Niste na ravnicama!";
    getch();
    return 0;
}    
