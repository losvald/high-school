#include <iostream.h>
#include <conio.h>
int c;
class hehe {
    public:
        static void brojac();
} a;
void hehe::brojac() {
    c = 5; }

int main() {
    hehe::brojac();
    cout << c;
    getch();
    return 0;
}        
