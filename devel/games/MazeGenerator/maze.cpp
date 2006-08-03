/*
 * maze.cpp
 *
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of MazeGenerator.
 *
 * MazeGenerator is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MazeGenerator is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MazeGenerator. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <conio.h>
#include <ctime>
#include <cctype>
#include <windows.h>
#define MAX 1001
#define MinGran 3
FILE *file;
using namespace std;
int polje[MAX][MAX];
char graf[MAX+1][2*(MAX+1)], bgraf[MAX+1][2*(MAX+1)]; char c = '\0';
int neigh[4][2] = {0,1,-1,0,0,-1,1,0};
int m, n, sx, sy, fx, fy, fg, gr, rev = 0, maxrev = 0, maxdist = 0, solved = 0;
vector<pair<int, int> > lista;
pair<int, int> par, prevpar;
void srnd() {
    srand((unsigned) time(NULL));
}
void cls()
{
  COORD coordScreen = { 0, 0 }; /* here's where we'll home the cursor */
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
  DWORD dwConSize; /* number of character cells in the current buffer */

  /* get the output console handle */
  HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
  /* get the number of character cells in the current buffer */
  GetConsoleScreenBufferInfo(hConsole, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  /* fill the entire screen with blanks */
  FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten);
  /* get the current text attribute */
  GetConsoleScreenBufferInfo(hConsole, &csbi);
  /* now set the buffer's attributes accordingly */
  FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten);
  /* put the cursor at (0, 0) */
  SetConsoleCursorPosition(hConsole, coordScreen);
  return;
}
int keytodir(char cc) {
    char a[] = {'D','W','A','S'};
    for(int i = 0; i < 4; ++i)
      if(toupper(cc) == a[i])
            return i;
    return -1;
}
int okstanje(int stanje) {
    if(stanje >= 0) return stanje < lista.size();
    stanje = -stanje--;
    if(par.first+neigh[stanje][0] < 0) return 0;
    if(par.second+neigh[stanje][1] < 0) return 0;
    if(par.first+neigh[stanje][0] >= m) return 0;
    if(par.second+neigh[stanje][1] >= n) return 0;
    if(polje[par.first+neigh[stanje][0]][par.second+neigh[stanje][1]] != -1) return 0;
    return 1;
}
void make_backup() {
    for(int i = 0; i <= m; ++i)
        for(int j = 0; j <=2*n; ++j)
                bgraf[i][j] = graf[i][j];
}
void load_backup() {
      for(int i = 0; i <= m; ++i)
        for(int j = 0; j <=2*n; ++j)
               graf[i][j] = bgraf[i][j];
}
int ucitaj() {
    char tmp[50], s[50], c;
    int r = rand()%fg;
    if(r == fg-1 && lista.size() >= MinGran) {
        r = rand()%gr;
        while(!okstanje(r)) r = rand()%gr;
        return lista.size()-r;
    }
    else {
        r = rand()%4;
        while(!okstanje(-(r+1))) r = rand()%4;
        return -(r+1);
    }
    return -5;
}
void remwall(int y, int x, int stanje) {
    if(stanje == 0) graf[y+1][2*x+2] = ' ';
    else if(stanje == 1) graf[y][2*x+1] = ' ';
    else if(stanje == 2) graf[y+1][2*x] = ' ';
    else if(stanje == 3) graf[y+1][2*x+1] = ' ';
}
int nowall(int y, int x, int stanje) {
    if(stanje == 0) {
        if(graf[y+1][2*x+2] == '|' || graf[y+1][2*x+2] == '_')
                return 0;
    }
    else if(stanje == 1) {
        if(graf[y][2*x+1] == '|' || graf[y][2*x+1] == '_')
                return 0;
    }
    else if(stanje == 2) {
        if(graf[y+1][2*x] == '|' || graf[y+1][2*x] == '_')
                return 0;
    }
    else if(stanje == 3) {
        if(graf[y+1][2*x+1] == '|' || graf[y+1][2*x+1] == '_')
                return 0;
    }
    return 1;

}
void drawdir(int y, int x, int stanje) {
    if(stanje == 0) graf[y+1][2*x+2] = '\0'+27;
    else if(stanje == 1) graf[y][2*x+1] = '\0'+25;
    else if(stanje == 2) graf[y+1][2*x] = '\0'+26;
    else if(stanje == 3) graf[y+1][2*x+1] = '\0'+24;
}
void drawpos(int y, int x) {
    for(int i = 0; i < 4; ++i) {
        if(y+neigh[i][0] >= 0 && y+neigh[i][0] < m &&
                x+neigh[i][1] >= 0 && x+neigh[i][1] < n)
          //if(polje[y+neigh[i][0]][x+neigh[i][1]] == polje[y][x]-1)
             if(nowall(y, x, i)) {
               drawdir(y, x, i);
                    break;
                }
    }
}
void drawpatharrow(int y, int x, int smjer) {
    if(y+neigh[smjer][0] >= 0 && y+neigh[smjer][0] < m &&
        x+neigh[smjer][1] >= 0 && x+neigh[smjer][1] < n) {
                if(smjer == 0) graf[y+1][2*x+2] = c+27;
                else if(smjer == 1) graf[y][2*x+1] = c+25;
                else if(smjer == 2) graf[y+1][2*x] = c+26;
                else if(smjer == 3) graf[y+1][2*x+1] = c+24;
    }
}
void print() {
    //printf("\n");
    cls();
    //printf("Destination(x, y) = (%d,%d)", fx+1, fy+1);
    //printf("\n");
    for(int i = 0; i <= m; ++i) {
        for(int j = 0; j <=2*n; ++j) {
          printf("%c", graf[i][j]);
        }
        printf("\n");
    }
    //printf("\n");
}
void fprint() {
    fprintf(file, "Start position (row,column) = (%d,%d)\n", sy+1, sx+1);
    fprintf(file, "Destination(row,column) = (%d,%d)", fy+1, fx+1);
    fprintf(file, "\n");
    for(int i = 0; i <= m; ++i) {
        for(int j = 0; j <=2*n; ++j) {
          fprintf(file, "%c", graf[i][j]);
        }
       fprintf(file, "\n");
    }
    fprintf(file, "\n");
}
void printp() {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
                printf("%4d", polje[i][j]);
                fprintf(file, "%4d", polje[i][j]);
        }
        printf("\n");
        fprintf(file, "\n");
    }
}
void printstat() {
    int avdist = 0;
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j) avdist+=polje[i][j];
    avdist /= m*n;
    printf("\n\n");
    fprintf(file, "\n\n");
    printf("Rev = %d\tMaxRev = %d\tDist = %d\tAvDist = %d\n", rev, maxrev, maxdist, avdist);
    fprintf(file, "Rev = %d\tMaxRev = %d\tDist = %d\tAvDist = %d\n", rev, maxrev, maxdist, avdist);
}
void ispis() {
    printf("\n"); fprintf(file, "\n");
    /*for(int i = 0; i < lista.size(); ++i) {
        pair<int, int> par2 = lista[i];
        printf("%d %d\n", par2.first, par.second);
    }*/
    pair<int, int> par2 = lista.back();
    printf("%d %d\n", par2.first, par.second);
    printf("\n");  fprintf(file, "\n");
}
void generate() {
    while(!lista.empty()) {
        par = lista.back();
                if(polje[par.first][par.second] > maxdist) {
                    maxdist = polje[par.first][par.second];
                    fy = par.first; fx = par.second;
                }
        int ok = 0;
        for(int i = 0; i < 4; ++i)
          if(par.first+neigh[i][0] >= 0 && par.first+neigh[i][0] < m
             && par.second+neigh[i][1] >= 0 && par.second+neigh[i][1] < n)
             if(polje[par.first+neigh[i][0]][par.second+neigh[i][1]] == -1) {
                 ok = 1;
                 break;
             }
        if(!ok) {lista.pop_back(); continue;}
        //print(); ispis();
        int stanje = ucitaj();
        if(stanje >= 0) {
            reverse(lista.begin()+stanje-1, lista.end());
            rev++;
            maxrev = max(maxrev, lista.size()-stanje+1);
        }
        else {
            stanje = -stanje--;
            remwall(par.first, par.second, stanje);
            polje[par.first+neigh[stanje][0]][par.second+neigh[stanje][1]] = polje[par.first][par.second]+1;
            lista.push_back(make_pair<int, int>(par.first+neigh[stanje][0], par.second+neigh[stanje][1]));
        }
    }
}
void reconstruct_path() {
    //printp();
    int x, y;
    x = fx; y = fy;
    int rj[500000]; int ind = 0;
  for(;;ind++) {
     if(y == sy && x == sx) break;
    for(int smjer = 0; smjer < 4; smjer++) {
               int ty =  y+neigh[smjer][0];
               int tx =  x+neigh[smjer][1];
           if(ty >= 0 && ty < m && tx >= 0 && tx < n)
            if(polje[ty][tx] == polje[y][x]-1 && nowall(y, x, smjer)) {
                rj[ind] = smjer;
                drawpatharrow(y, x, smjer);
                y = ty; x = tx;
                break;
            }
    }
  }
  if(!solved) print();
  fprint();
  printf("\n\n"); fprintf(file, "\n\n");
  for(int i = ind-1; i >= 0; --i) {
      if(rj[i] == 0) {printf("%c", c+27); fprintf(file,"L"); }
      else if(rj[i] == 1) {printf("%c",c+25); fprintf(file, "D"); }
      else if(rj[i] == 2) {printf("%c",c+26); fprintf(file, "R"); }
      else if(rj[i] == 3) {printf("%c",c+24); fprintf(file, "U"); }
  }
  printf("\n\n"); fprintf(file, "\n\n");
}
void igraj() {
    make_backup();
    printf("\nNow try to solve the maze!\n");
    printf("Use W, A, S or D to move through the maze.\n");
    printf("Use Q to Quit, R to Restart the position\n");
    printf("Press any key to continue\n"); getch();
    print(); fprint();
    clock_t st = clock();
    int x, y, lx, ly; char ch;
    set<pair<int, int> > bio;
    bio.insert(make_pair<int, int>(sy,sx));
    x = lx = sx; y = ly = sy;
    for(;;) {
        if(x == fx && y == fy) {
            int yourtime = (int) ((clock()-st)/1000);
            int yourh = yourtime/3600; yourtime %= 3600;
            int yourmin = yourtime/60; yourtime %= 60;
            int yoursec = yourtime;
            printf("\nCongratulations! You have solved the puzzle in %02d:%02d:%02d (hh:mm:ss)\n",
             yourh, yourmin, yoursec);
             solved = 1;
            load_backup();
            break;
        }
        ch = getch();
        if(ch == 'q' || ch == 'Q') {
            printf("Better luck next time!\n");
            load_backup();
            break;
        }
        else if(ch == 'r' || ch == 'R') {
            x = lx = sx; y = ly = sy;
            bio.clear();
            bio.insert(make_pair<int, int>(sy,sx));
            load_backup();
            print();
            //st = clock();
        }
        else if(keytodir(ch) != -1) {
                int smjer = keytodir(ch);
                if(nowall(y, x, smjer)) {
                    if(bio.find(make_pair<int, int>(y+neigh[smjer][0],x+neigh[smjer][1]))
                        != bio.end())
                    {
                        bio.erase( bio.find(make_pair<int, int>(y+neigh[smjer][0],x+neigh[smjer][1])) );
                        remwall(y, x, smjer);
                        y+=neigh[smjer][0]; x+=neigh[smjer][1];
                        print();
                    }
                    else {
                        bio.insert(make_pair<int, int>(y,x));
                        y+=neigh[smjer][0]; x+=neigh[smjer][1];
                        drawpatharrow(y, x, (smjer+2)%4);
                        print();
                    }
                }
        }
    }
}
void init() {
    for(int j = 0; j <= 2*n; ++j) {
         if(j%2) graf[0][j] = '_';
         else graf[0][j] = ' ';
    }
    for(int i = 1; i <= m; ++i)
      for(int j = 0; j <= 2*n; ++j) {
         if(j%2) graf[i][j] = '_';
         else graf[i][j] = '|';
      }
    for(int i = 0; i < m; ++i)
      for(int j = 0; j < n; ++j)
        polje[i][j] = -1;
    polje[sy][sx] = 0;
    file = fopen("maze.txt", "w");
}
void intro() {
    printf("Welcome to MazeGenerator v1.0 by Leo\n\n");
    printf("This program generates random mazes based upon entered parameters.\n");
    printf("Once the maze is generated, you will try to solve it.\n");
    printf("The maze itself and the solution will be saved in \"maze.txt\" file.\n");
    printf("\n");
}
void upis() {
    printf("Enter Dimensions (row) (column): "); scanf("%d %d", &m, &n);
    printf("Enter Branching Factor (higher = maze is more dense): "); scanf("%d", &fg);
    printf("Enter Length Factor (higher =  false ways are longer): "); scanf("%d", &gr);
    printf("Enter Start Position (row) (column)"); scanf("%d %d", &sy, &sx); --sy; --sx;
    getchar();
    lista.push_back(make_pair<int, int>(sy, sx));
}
int main() {
  srnd();
    intro();
    upis();
    init();
    generate();
    drawpos(sy, sx); drawpos(fy, fx);
    igraj();
    reconstruct_path();
    printstat();
    scanf("\n");
    return 0;
}
/*
Up 24
Down 25
Right 26
Left 27

 _ _ _
|_|_|_|
|_|_|_|
|_|_|_|
|_|_|_|
2 1 -> 2 3   U    y 2*x+1
2 1 -> 4 3   D    y+2 2*x+1
2 1 -> 3 2   L    y+1 2*x
2 1 -> 3 4   R    y+1 2*x+2
*/
