#include <cstdio>
int pod(int x, int y) {
    if(!y) throw -32000;
    return x/y;
}
int main() {
    for(;;) {
        int x, y;
        scanf("%d %d", &x, &y);
        try { 
            printf("%d\n", pod(x, y));
        } 
        catch (int g) {
            if(g == -32000)
              printf("Zabranjeno dijeljenje sa 0.\n");
        }
        if(!x && !y) break;
    }
    return 0;
}            
                 
