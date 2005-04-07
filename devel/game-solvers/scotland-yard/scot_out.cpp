#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ofstream out("scot_out.txt", ios::out);
    for(int i = 100; i < 199; i++) {
        for(int j = 1; j <= 8; j++)
          out << "        polje[" << i << "].br[" << j << "] = ; polje[" << i << "].voz["
              << j << "] = '';\n";
        out << endl;
    }
    getchar();
    return 0;
}
