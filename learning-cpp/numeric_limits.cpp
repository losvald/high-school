#include <limits.h>
#include <iostream.h>
#include <conio.h>
#include <cmath>
#include <iomanip.h>
using namespace std;
int main() {
    cout << "int - " << INT_MAX << endl;
    cout << "long int - " << LONG_MAX << endl;
    cout << "long long int - " << LONG_LONG_MAX << endl;
    cout << "float - " << numeric_limits<float>::max() << endl;
    cout << "double - " << numeric_limits<double>::max() << endl;
    getch();
    return 0;
}    
