#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
struct point {
    int x, y;
    point(){};
    point(int x, int y) {this->x = x; this->y = y;};
};    
int main() {
    vector< point > v;
    int t, x, y;
    for(int i = 0; i < 5; i++) {
        scanf("%d %d", &x, &y);
        point t;
        t.x = x;
        t.y = y;
        v.push_back( point( x, y));
        
    }
    
    for(int i = 0; i < v.size(); i++)
     printf("%d %d\t", v[i].x, v[i].y);
         
    scanf("%d", &t);
    return 0;
}    
