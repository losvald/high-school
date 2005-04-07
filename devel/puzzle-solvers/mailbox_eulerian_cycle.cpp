/*
 * Copyright (C) 2005 Leo Osvald <leo.osvald@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
int val[100], V = 8, id = -1;
int a[10][10];
void napisi() {
    for(int i = 0; i < V; i++) printf("%d ", val[i+1]);
    printf("\n");
}
void visit(int k) {
    int t;
    val[k] = ++id;
    if(id == 5) napisi();
    for(t = 0; t < V; t++) {
      if(a[k][t])
        if(val[t] == 0) visit(t);
    }
    id--; val[k] = 0;
}
int main() {
    //inicijalizacija
    a[0][1] = 1; a[1][0] = 1;
    a[1][2] = 1;   a[2][1] = 1;
    a[2][3] = 1;   a[3][2] = 1;
    a[3][4] = 1;   a[4][3] = 1;
    a[2][4] = 1;   a[4][2] = 1;
    a[0][3] = 1;   a[3][0] = 1;
    a[0][2] = 1;   a[2][0] = 1;
    a[1][3] = 1;   a[3][1] = 1;
    //gotovo
    visit(0);
    printf("\nGotovo!");
    getchar();
    return 0;
}
