/*
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
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
#include <iostream>
#include <ctime>
#define N 64
FILE *file, *fout;
int m;
int polje[N][N];
int id = 0, V = N;
int val[N]; int sol = 0;
void init() {
    file = fopen("knight.txt", "r");
    fout = fopen("knight_out.txt", "w");
    fscanf(file, "%d", &m);
    for(int i = 0; i < m; i++) {
        int a, b;
        fscanf(file, "%d", &a);
        for(int j = 0; j < a; j++) {
            fscanf(file, "%d", &b);
            b--; polje[i][b] = 1;
        }
    }
       /*for(int i = 0; i < m; i++) {
           for(int j = 0; j < m; j++) printf("%d ",polje[i][j]);
           printf("\n");
       }    */
}
void visit(int t) {
    val[t] = ++id;
    if(id == V) {
        for(int i = 1; i <= N; i++)
          for(int j = 0; j < N; j++)
            if(val[j] == i) fprintf(fout,"%d ", j+1);
        fprintf(fout,"\n");
        sol++;
        //scanf("%d", &t); exit(0);
    }
    for(int i = 0; i < m; i++) {
        if(polje[t][i] && !val[i]) {
            visit(i);
        }
    }
    id--; val[t] = 0;
}
int main() {
     init(); printf("Starting square: ");
     int x; scanf("%d", &x);
     double st = clock();
     visit(x-1);
     printf("\nDone (%lf ms) - %d!", (clock()-st), sol);
     fprintf(fout, "\n\n\n\nDone (%lf ms) - %d!", (clock()-st), sol);
     fclose(fout); fclose(file);
    int tmp; scanf("%d", &tmp);
    return 0;
}
