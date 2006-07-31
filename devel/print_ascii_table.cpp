#include <cstdio>
int main() {
    for(int i = 1; i <= 256; ++i) printf("%d = %c\n", i, '\0'+i);
    scanf("\n");
    return 0;
}    
