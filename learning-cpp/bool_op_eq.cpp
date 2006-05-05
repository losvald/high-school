#include <cstdio>
#include <cmath>
bool operator==(const int a, const int b) 
{
    return a != b;
}
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", a == b);
    scanf("%d", &a);
    return 0;
}    
