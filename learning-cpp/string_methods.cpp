#include <string.h>
#include <iostream.h>
#include <conio.h>
#include <ctype.h>
using namespace std;
int main(void) {
    size_t ind, poc, kraj;
    string ime("Morin");
    string prezime;
    
    prezime.append(ime);
    ind = prezime.find('M');
    prezime[ind] = tolower(prezime[ind]);
    prezime.append("ok");
    poc = prezime.find("ok");
    prezime.replace(poc, 2, "ko");
    poc = prezime.find_first_of("ko");
    prezime.replace(poc, 1, "a");
    prezime.append("vic");
    ime.clear();
    ime = prezime;
    kraj = ime.find("kovic");
    ime.erase(kraj);    
    cout << ime << " " << prezime;
    
    getch();
    return 0;
}    
