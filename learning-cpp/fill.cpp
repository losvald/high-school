#include <iostream.h>
#include <conio.h>
#include <string.h>
using namespace std;
struct deno {
    int a;
    void zam();
} den, leo;
void deno::zam() {swap(den, leo);}    
int main() {
    int a, b;
    cin >> a >> b;
    cout.width(3);
    cout.fill('0');
    cout << a << ":";
    cout.width(3);
    cout.fill('0');
    cout << b;
    cin >> den.a >> leo.a;
    den.zam();
    cout << den.a << leo.a; 
    getch();
    return 0;
}    
