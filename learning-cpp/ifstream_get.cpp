#include <string.h>
#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
int main() {
    ifstream in("vjerot13.txt", ios::in);
    ofstream out("vj.txt", ios::out);
    char c;
    const bool da = true;
    while (da) {
      in.get(c); 
      if(c == '!')
        break;
      if(c != ' ')  
        out << c;
    }
    getch();
}          
