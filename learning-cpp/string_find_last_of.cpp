#include <string.h>
#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
using namespace std;
int main() {
    string ime;
    ofstream b("10.txt", ios::out);
    cin >> ime;
    size_t ind = ime.find_last_of(".");
    if((ind < ime.size()-4 && ime.size() > 3) || ind > ime.size())
      ime.append(".txt");
    cout << ime;
    b << ime;
    getch();
    return 0;
}    
