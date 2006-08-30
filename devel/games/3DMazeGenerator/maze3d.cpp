/*
 * maze3d.cpp
 *
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of 3DMazeGenerator.
 *
 * 3DMazeGenerator is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * 3DMazeGenerator is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 3DMazeGenerator. If not, see
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
#define MAX 101
#define MinGran 3
FILE *file;
using namespace std;
struct point {
    int x, y, z;
    point() {}
    point(int z, int y, int x) {
        this->z = z;
        this->y = y;
        this->x = x;
    }
} p;
bool operator<(const point &a, const point &b) {
    return MAX*MAX*a.z+MAX*a.y+a.x < MAX*MAX*b.z+MAX*b.y+b.x;
}
int polje[MAX][MAX][MAX];
char graf[2*(MAX+1)][2*(MAX+1)][2*(MAX+1)], bgraf[2*(MAX+1)][2*(MAX+1)][2*(MAX+1)], c = '\0';
int neigh[6][3] = {0,0,1, 0,-1,0, 1,0,0,  0,0,-1, 0,1,0, -1,0,0};
int h, m, n, sx, sy, sz, fx, fy, fz, fg, gr, rev = 0, maxrev = 0, maxdist = 0, solved = 0;
int currdim = 0;
vector<point> lista;
//pair<int, int> par;
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
int nowall(int z, int y, int x, int stanje) {
    if(stanje == 0) {
        if(graf[2*z+1][2*y+1][2*x+2] == char(c+219))
                return 0;
    }
    else if(stanje == 1) {
        if(graf[2*z+1][2*y][2*x+1] == char(c+219))
                return 0;
    }
    else if(stanje == 2) {
        if(graf[2*z+2][2*y+1][2*x+1] == char(c+219))
                return 0;
    }
    else if(stanje == 3) {
        if(graf[2*z+1][2*y+1][2*x] == char(c+219))
                return 0;
    }
    else if(stanje == 4) {
        if(graf[2*z+1][2*y+2][2*x+1] == char(c+219))
                return 0;
    }
    else if(stanje == 5) {
        if(graf[2*z][2*y+1][2*x+1] == char(c+219))
                return 0;
    }
    return 1;

}
int keytodir(char cc, int dim) {
    char a[3][6] = {{'D','W','F','A','S','G'},
                     {'A','G','S','D','F','W'},
                     {'S','G','D','W','F','A'}};
    for(int i = 0; i < 6; ++i)
      if(toupper(cc) == a[0][i]) {
          for(int j = 0; j < 6; ++j)
             if(a[dim][i] == a[0][j])
               return j;
      }
    return -1;
}
inline int okz(int l, int i, int j, int cz, int cy, int cx) {
    int a = 0;
    int nldown[3][3] = {1,0,0, 0,1,0, 0,0,1};
    int nlup[3][3] = {-1,0,0, 0,-1,0, 0,0,-1};
    if(!(i%2) && i != -1) return 0;
    if(!(j%2) && j != -1) return 0;
    if(!(l%2) && l != -1) return 0;
    int x, y, z;
    if(l != -1) z = (l-1)/2; else z = cz;
    if(i != -1) y = (i-1)/2; else y = cy;
    if(j != -1) x = (j-1)/2; else x = cx;
    if(z < 0 || z >= h || y < 0 || y >= m || x < 0 || x >= n) return 0;
    if(nowall(z, y, x, keytodir('F', currdim))) a = 1;
    if(nowall(z, y, x, keytodir('G', currdim))) {
       if(a) a = 3;
       else a = 2;
    }
    return a;
}
int okstanje(int stanje) {
    if(stanje >= 0) return stanje < lista.size();
    stanje = -stanje--;
    if(p.z+neigh[stanje][0] < 0) return 0;
    if(p.y+neigh[stanje][1] < 0) return 0;
    if(p.x+neigh[stanje][2] < 0) return 0;
    if(p.z+neigh[stanje][0] >= h) return 0;
    if(p.y+neigh[stanje][1] >= m) return 0;
    if(p.x+neigh[stanje][2] >= n) return 0;
    if(polje[p.z+neigh[stanje][0]][p.y+neigh[stanje][1]][p.x+neigh[stanje][2]] != -1) return 0;
    return 1;
}
void make_backup() {
    for(int l = 0; l <= 2*h; ++l)
      for(int i = 0; i <= 2*m; ++i)
        for(int j = 0; j <=2*n; ++j)
                bgraf[l][i][j] = graf[l][i][j];
}
void load_backup() {
    for(int l = 0; l <= 2*h; ++l)
      for(int i = 0; i <= 2*m; ++i)
        for(int j = 0; j <=2*n; ++j)
               graf[l][i][j] = bgraf[l][i][j];
}
int ucitaj() {
    int r = rand()%fg;
    if(r == fg-1 && lista.size() >= MinGran) {
        r = rand()%gr;
        while(!okstanje(r)) r = rand()%gr;
        return lista.size()-r;
    }
    else {
        r = rand()%6;
        while(!okstanje(-(r+1))) r = rand()%6;
        return -(r+1);
    }
    return -10;
}
void remwall(int z, int y, int x, int stanje) {
    if(stanje == 0) graf[2*z+1][2*y+1][2*x+2] = ' ';
    else if(stanje == 1) graf[2*z+1][2*y][2*x+1] = ' ';
    else if(stanje == 2) graf[2*z+2][2*y+1][2*x+1] = ' ';
    else if(stanje == 3) graf[2*z+1][2*y+1][2*x] = ' ';
    else if(stanje == 4) graf[2*z+1][2*y+2][2*x+1] = ' ';
    else if(stanje == 5) graf[2*z][2*y+1][2*x+1] = ' ';
}
void drawpos(int z, int y, int x, char cpos = 'D') {
    graf[2*z+1][2*y+1][2*x+1] = cpos;
}
void drawpatharrow(int z, int y, int x, int smjer) {
    if(z+neigh[smjer][0] >= 0 && z+neigh[smjer][0] < h &&
       y+neigh[smjer][1] >= 0 && y+neigh[smjer][1] < m &&
        x+neigh[smjer][2] >= 0 && x+neigh[smjer][2] < n) {
                if(smjer == 0) graf[2*z+1][2*y+1][2*x+2] = c+27;
                else if(smjer == 1) graf[2*z+1][2*y][2*x+1] = c+25;
                else if(smjer == 2) graf[2*z+1][2*y+1][2*x] = c+26;
                else if(smjer == 3) graf[2*z+1][2*y+2][2*x+1] = c+24;
    }
}
void mark(int z, int y, int x, int smjer, char cm) {
    if(z+neigh[smjer][0] >= 0 && z+neigh[smjer][0] < h &&
       y+neigh[smjer][1] >= 0 && y+neigh[smjer][1] < m &&
        x+neigh[smjer][2] >= 0 && x+neigh[smjer][2] < n) {
                if(smjer == 0) graf[2*z+1][2*y+1][2*x+2] = cm;
                else if(smjer == 1) graf[2*z+1][2*y][2*x+1] = cm;
                else if(smjer == 2) graf[2*z+2][2*y+1][2*x+1] = cm;
                else if(smjer == 3) graf[2*z+1][2*y+1][2*x] = cm;
                else if(smjer == 4) graf[2*z+1][2*y+2][2*x+1] = cm;
                else if(smjer == 5) graf[2*z][2*y+1][2*x+1] = cm;
    }
    //bas to polje
    if(cm != ' ') graf[2*z+1][2*y+1][2*x+1] = cm;
}
void print(int hh, int mm, int nn, int dim) {
    cls();
    drawpos(fz, fy, fx);
    if(dim == 0) {
      for(int i = 0; i <= 2*m; ++i) {
        for(int j = 0; j <= 2*n; ++j) {
          int a = okz(-1, i, j, hh, mm, nn);
          if(!a || ((i-1)/2 == fy && (j-1)/2 == fx)) printf("%c", graf[2*hh+1][i][j]);
          else if(a == 1) printf("%c", c+25);
          else if(a == 2) printf("%c", c+24);
          else if(a == 3) printf("%c", c+18);
        }
        printf("\n");
      }
    }
    else if(dim == 1) {
      for(int l = 0; l <= 2*h; ++l) {
        for(int j = 2*n; j >= 0; --j) {
          int a = okz(l, -1, j, hh, mm, nn);
          if(!a || ((l-1)/2 == fz && (j-1)/2 == fx)) printf("%c", graf[l][2*mm+1][j]);
          else if(a == 1) printf("%c", c+25);
          else if(a == 2) printf("%c", c+24);
          else if(a == 3) printf("%c", c+18);
        }
        printf("\n");
      }
    }
    else {
      for(int l = 0; l <= 2*m; ++l) {
        for(int i = 0; i <= 2*m; ++i) {
          int a = okz(l, i, -1, hh, mm, nn);
          if(!a || ((l-1)/2 == fz && (i-1)/2 == fy)) printf("%c", graf[l][i][2*nn+1]);
          else if(a == 1) printf("%c", c+25);
          else if(a == 2) printf("%c", c+24);
          else if(a == 3) printf("%c", c+18);
        }
        printf("\n");
      }
    }
    printf("\nCurrent position (z y x): %02d %02d %02d", hh+1, mm+1, nn+1);
    printf("\nDestination (z y y): %02d %02d %02d\n", fz+1, fy+1, fx+1);
}
void fprint(int hh, int da = 0) {
    fprintf(file, "Level %3d\n", hh+1);
    for(int i = 0; i <= 2*m; ++i) {
        for(int j = 0; j <=2*n; ++j) {
          int a = okz(-1, i, j, hh, 0, 0);
          if(!da || !a || ((i-1)/2 == fy && (j-1)/2 == fx)) {
              if(graf[2*hh+1][i][j] == char(c+219))
                 fprintf(file, "#");
              else fprintf(file, "%c", graf[2*hh+1][i][j]);
          }
          else if(a == 1) fprintf(file, "%c", 'B');
          else if(a == 2) fprintf(file, "%c", 'A');
          else if(a == 3) fprintf(file, "%c", '2');
        }
       fprintf(file, "\n");
    }
    fprintf(file, "\n");
}
void printstat() {
    int avdist = 0;
    for(int l = 0; l < h; ++l)
      for(int i = 0; i < m; ++i)
          for(int j = 0; j < n; ++j) avdist+=polje[l][i][j];
    avdist /= m*n*h;
    printf("\n\n");
    fprintf(file, "\n\n");
    printf("Rev = %d\tMaxRev = %d\tDist = %d\tAvDist = %d\n", rev, maxrev, maxdist, avdist);
    fprintf(file, "Rev = %d\tMaxRev = %d\tDist = %d\tAvDist = %d\n", rev, maxrev, maxdist, avdist);
}
void generate() {
    while(!lista.empty()) {
        p = lista.back();
                if(polje[p.z][p.y][p.x] > maxdist) {
                    maxdist = polje[p.z][p.y][p.x];
                    fz = p.z; fy = p.y; fx = p.x;
                }
        int ok = 0;
        for(int i = 0; i < 6; ++i)
          if(p.z+neigh[i][0] >= 0 && p.z+neigh[i][0] < h &&
             p.y+neigh[i][1] >= 0 && p.y+neigh[i][1] < m
             && p.x+neigh[i][2] >= 0 && p.x+neigh[i][2] < n)
             if(polje[p.z+neigh[i][0]][p.y+neigh[i][1]][p.x+neigh[i][2]] == -1) {
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
            remwall(p.z, p.y, p.x, stanje);
            polje[p.z+neigh[stanje][0]][p.y+neigh[stanje][1]][p.x+neigh[stanje][2]] = polje[p.z][p.y][p.x]+1;
            lista.push_back( point(p.z+neigh[stanje][0], p.y+neigh[stanje][1], p.x+neigh[stanje][2]) );
        }
    }
}
void reconstruct_path() {
    //printp();
    int x, y, z;
    x = fx; y = fy; z = fz;
    int rj[500000]; int ind = 0;
  for(;;ind++) {
     if(y == sy && x == sx && z == sz) break;
    for(int smjer = 0; smjer < 6; smjer++) {
               int tz =  z+neigh[smjer][0];
               int ty =  y+neigh[smjer][1];
               int tx =  x+neigh[smjer][2];

           if(tz >= 0 && tz < h && ty >= 0 && ty < m && tx >= 0 && tx < n)
            if(polje[tz][ty][tx] == polje[z][y][x]-1 && nowall(z, y, x, smjer)) {
                rj[ind] = smjer;
                //drawpatharrow(y, x, smjer);
                mark(z, y, x, smjer, '.');
                z = tz; y = ty; x = tx;
                break;
            }
    }
  }
  drawpos(fz, fy, fx);
  if(!solved) print(fz, fy, fx, 0);
  for(int i = 0; i < h; ++i) fprint(i);
  printf("\n\n"); fprintf(file, "\n\n");
  for(int i = ind-1; i >= 0; --i) {
      if(rj[i] == 0) {printf("%c", c+17); fprintf(file,"L"); }
      else if(rj[i] == 1) {printf("%c",c+31); fprintf(file, "D"); }
      else if(rj[i] == 2) {printf("%c",c+24); fprintf(file, "A"); }
      else if(rj[i] == 3) {printf("%c",c+16); fprintf(file, "R"); }
      else if(rj[i] == 4) {printf("%c",c+30); fprintf(file, "U"); }
      else if(rj[i] == 5) {printf("%c",c+25); fprintf(file, "B"); }
  }
  printf("\n\n"); fprintf(file, "\n\n");
}
void igraj() {
    make_backup();
    printf("\nNow try to solve the maze!\n");
    printf("Use W, A, S or D to move through the maze.\n");
    printf("Use F to go one level down, G to go one level up.\n");
    printf("Use Q to Quit, R to Restart the position\n");
    printf("Use X, Y, Z to change the view to yz, xz, xy (xy = default)\n");
    printf("Press any key to continue\n"); getch();
    print(sz, sy, sx, 0);
      for(int i = 0; i < h; ++i) fprint(i, 1);
       fprintf(file, "\n\nSOLUTION:\n\n");
    clock_t st = clock();
    int x, y, z, lx, ly, lz; char ch;
    set<point> bio;
    bio.insert( point(sz,sy,sx) );
    x = lx = sx; y = ly = sy; z = lz = sz;
    for(;;) {
        if(x == fx && y == fy && z == fz) {
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
            z = lz = sz; x = lx = sx; y = ly = sy;
            bio.clear();
            bio.insert(point(sz,sy,sx));
            load_backup();
            print(sz, sy, sx, 0);
            //st = clock();
        }
        else if(keytodir(ch, currdim) != -1) {
                int smjer = keytodir(ch, currdim);
                if(nowall(z, y, x, smjer)) {
                    if(bio.find(point(z+neigh[smjer][0],y+neigh[smjer][1],x+neigh[smjer][2]))
                        != bio.end())
                    {
                       bio.erase( bio.find(point(z+neigh[smjer][0],y+neigh[smjer][1],x+neigh[smjer][2])) );
                        //remwall(y, x, smjer);
                         graf[2*z+1][2*y+1][2*x+1] = ' ';
                        z+=neigh[smjer][0]; y+=neigh[smjer][1]; x+=neigh[smjer][2];
                        mark(z, y, x, (smjer+3)%6, ' ');
                        print(z, y, x, currdim);
                    }
                    else {
                       bio.insert(point(z,y,x));
                        z+=neigh[smjer][0]; y+=neigh[smjer][1]; x+=neigh[smjer][2];
                        //drawpatharrow(y, x, (smjer+2)%4);
                          mark(z, y, x, (smjer+3)%6, '.');
                        print(z, y, x, currdim);
                    }
                }
        }
        else if(ch == 'z' || ch == 'Z') {
            currdim = 0;
            print(z, y, x, 0);
        }
        else if(ch == 'y' || ch == 'Y') {
            currdim = 1;
            print(z, y, x, 1);
        }
        else if(ch == 'x' || ch == 'X') {
            currdim = 2;
            print(z, y, x, 2);
        }
    }
}
void introf() {
    fprintf(file,"This is 3D Maze generated with the following parameters:\n");
    fprintf(file, "%d %d %d %d %d %d %d %d\n", h, m, n, fg, gr, sz, sy, sx);
    fprintf(file, "Help: R = Right\tU = Up\tL = Left\tD = Down\n");
    fprintf(file, "B = Level down (Below)\tA = Level up (Above)\n");
    fprintf(file, "(2 = Level down + Level up)\n");
    fprintf(file, "Note: Solution is represented in xy view!");
    fprintf(file, "\n\n");
    fprintf(file, "Start position (level,row,column) = (%d,%d,%d)\n", sz+1, sy+1, sx+1);
    fprintf(file, "Destination(level,row,column) = (%d,%d,%d)", fz+1, fy+1, fx+1);
    fprintf(file, "\n");
}
void init() {
    for(int l = 0; l <= 2*h; ++l)
      for(int i = 0; i <= 2*m; ++i)
        for(int j = 0; j <= 2*n; ++j) {
           if(j%2 && i%2 && l%2) graf[l][i][j] = ' ';
           else graf[l][i][j] = char(c+219);
        }
    for(int l = 0; l < h; ++l)
      for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
          polje[l][i][j] = -1;
    polje[sz][sy][sx] = 0;
    file = fopen("maze3d.txt", "w");
    introf();
}
void intro() {
    printf("Welcome to 3DMazeGenerator v2.0 by Leo\n\n");
    printf("This program generates random mazes based upon entered parameters.\n");
    printf("Once the maze is generated, you will try to solve it.\n");
    printf("The maze itself and the solution will be saved in \"maze3d.txt\" file.\n");
    printf("\n");
}
void upis() {
    printf("Enter Dimensions (level) (row) (column): "); scanf("%d %d %d", &h, &m, &n);
    printf("Enter Branching Factor (higher = maze is more dense): "); scanf("%d", &fg);
    printf("Enter Length Factor (higher =  false ways are longer): "); scanf("%d", &gr);
    printf("Enter Start Position (level) (row) (column)"); scanf("%d %d %d", &sz, &sy, &sx);
    --sz; --sy; --sx;
    getchar();
    lista.push_back(point(sz, sy, sx));
}
int main() {
  srnd();
    intro();
    upis();
    init();
    generate();
    drawpos(sz, sy, sx, 'S'); drawpos(fz, fy, fx);
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
