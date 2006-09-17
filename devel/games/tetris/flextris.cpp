/*
 * flextris.cpp
 *
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Flextris.
 *
 * Flextris is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Flextris is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Flextris. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
using namespace std;
#define MAX_H 22
#define MAX_W 10
#define H_CENT 4
#define SCORE_PER_LEVEL 10000
#define INF 1000000000
struct patt {
    string pos[4][4];
};
struct tetris;
typedef map<string, patt>::iterator miter;
struct pattern {
    string pos[4][4];
    int x, y;
    int smjer;
    pattern(string s, tetris&);
    void move(int y, int x) {this->y+=y; this->x+=x;} const
    void rotate() {
        smjer = (smjer+1)%4;
    }
};
struct tetris {
    vector<string> lobl;
    map<string, patt> oblici;
    int polje[MAX_H][MAX_W], bpolje[MAX_H][MAX_W];
    int todir[3][2]; //y x
    int maxobl;
    int score;
    int level;
    int hmax;  //najvisa tocka
    int paused;
    int ncut, mincut, blink;
    int ms_jump, ms_delay, ms_poc;
    string thisp, nextp;
    char c1,c2,c3;
    void getseed() {
        srand((unsigned) time(NULL));
    }
    string getnext() {
        return lobl[rand()%maxobl];
    }
    inline void cls()
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
    void init() {
        paused = 0;
        score = 0; level = 1; hmax = 0;
        for(int i = 0; i < MAX_H; ++i)
          for(int j = 0; j < MAX_W; ++j)
            polje[i][j] = bpolje[i][j] = 0;
    }
    void make_backup() {
        for(int i = 0; i < MAX_H; ++i)
          for(int j = 0; j < MAX_W; ++j)
            bpolje[i][j] = polje[i][j];
    }
    void load_backup() {
        for(int i = 0; i < MAX_H; ++i)
          for(int j = 0; j < MAX_W; ++j)
            polje[i][j] = bpolje[i][j];
    }
    void playintro() {
        printf("Welcome to Tetris v1.0\tby Leo\n\n");
        printf("Controls:\tW - rotate\n");
        printf("\t\tS - speed down\n");
        printf("\t\tA - move left\n");
        printf("\t\tD - move right\n\n");
        printf("Press any key to Start a New game.\n");
        getch();
    }
    void printover() {
        cls();
        printf("GAME OVER!\n\n");
        printf("Your Score is %7d\n\n\n", score);
        double poc = clock(); while((clock()-poc) < 1000) ;
        printf("Thanks for playing. Press Q key to Quit.\n\n\n");
        printf("Please send bug reports to <leo.osvald@gmail.com>\n");
        while(toupper(getch()) != 'Q') ;

    }
    inline void print(pattern& pat) {
        cls();
        for(int i = MAX_H-1; i >= MAX_H-1-1; --i) {
            printf(" ");
            for(int j = 0; j < MAX_W; ++j) {
              if(polje[i][j] || (pat.y-i < 4 && pat.y-i >= 0 && j-pat.x < 4 && j-pat.x >= 0
                && pat.pos[pat.smjer][pat.y-i][j-pat.x] == '1')) printf("%c", c2);
              else printf(" ");
            }
            if(i == MAX_H-1-1) printf("\tNext:");
            printf("\n");
        }
        for(int i = MAX_H-1-2; i >= 0; --i) {
            printf("%c", c1);
            for(int j = 0; j < MAX_W; ++j) {
              if(polje[i][j] || (pat.y-i < 4 && pat.y-i >= 0 && j-pat.x < 4 && j-pat.x >= 0
                && pat.pos[pat.smjer][pat.y-i][j-pat.x] == '1')) {
                if(blink && i >= mincut && i < mincut+ncut) printf("%c", c3);
                else printf("%c", c2);
              }
              else printf(" ");
            }
            printf("%c", c1);
            if(MAX_H-1-2 - i < 4) {
                pattern nextpat(nextp, *this);
                printf("\t");
                for(int j = 0; j < 4; ++j) {
                  if(nextpat.pos[0][MAX_H-1-2-i][j] == '1') printf("%c",c2);
                  else printf(" ");
                }
            }
            printf("\n");
        }
        for(int j = 0; j < MAX_W+2; ++j) printf("%c", c1);
        if(paused) printf("\tPAUSED!");
        printf("\n\nLevel %2d\tSCORE\t%7d\t", level, score);
    }
    int lock(pattern& pat) {
       for(int i = 0; i < 4; ++i)
          for(int j = 0; j < 4; ++j) {
              if(pat.pos[pat.smjer][i][j]=='1') {
                polje[pat.y-i][pat.x+j] = 1;
                hmax = max(hmax, pat.y-i+1);
              }
          }
       if(hmax >= MAX_H-2) return 1;
       ncut = 0; mincut = INF;
       for(int red = pat.y-3; red <= pat.y; ++red) {
           if(red < 0) {red = -1; continue; }
           int cut = 1;
           for(int st = 0; st < MAX_W; ++st)
             if(!polje[red][st]) {cut = 0; break;}
           if(cut) {
               mincut = min(mincut, red);
               ++ncut;
           }
       }
      if(ncut) {
           //blinkaj pojedene redove
           blink = 1;
           print(pat);
              //pauziraj 500ms
               double poc = clock();
               while((clock()-poc) < 500) ;
           blink = 0;
           print(pat);

           for(int i = mincut; i < mincut+ncut; ++i)
             for(int j = 0; j < MAX_W; ++j) polje[i][j] = 0; //brisanje reda

           //pomak dolje
           if(hmax) {
           for(int i = mincut+ncut; i <= hmax+ncut; ++i)
             for(int j = 0; j < MAX_W; ++j)
               polje[i-ncut][j] = polje[i][j];
             }
           hmax-=ncut;
       }
       if(ncut == 1) score+=level*40;
       else if(ncut == 2) score+=level*100;
       else if(ncut == 3) score+=level*300;
       else if(ncut == 4) score+=level*1200;
       level = score/int(SCORE_PER_LEVEL)+1;
       ms_delay = ms_poc-(level-1)*ms_jump;

       return 0;
    }
    int okrotate(pattern& pat) {
        int nextsmjer = (pat.smjer+1)%4;
        for(int i = 0; i < 4; ++i)
          for(int j = 0; j < 4; ++j) {
              if((pat.y-i < 0 || pat.x+j < 0 || pat.x+j >= MAX_W || polje[pat.y-i][pat.x+j])
              && pat.pos[nextsmjer][i][j]=='1')
               return 0;
          }
        return 1;
    }
    void rotate(pattern& pat) {
        pat.rotate();
        print(pat);
    }
    int okdir(int dir, pattern& pat) {
        const int &y = todir[dir][0], &x = todir[dir][1];
        for(int i = 0; i < 4; ++i)
          for(int j = 0; j < 4; ++j) {
              if(pat.pos[pat.smjer][i][j]=='1' && (j+pat.x+x < 0 || j+pat.x+x >= MAX_W || -i+pat.y+y < 0 ||
                polje[ -i+pat.y+y ][ j+pat.x+x ]) )
                  return 0;
          }
        return 1;

    }
    void movedir(int dir, pattern& pat) {
        pat.move(todir[dir][0], todir[dir][1]);
        print(pat);
    }
    int run1(pattern& a) {
        double i = 1, j;
        double poc, kraj;
        int last = 0;
        poc = clock();

        while( (j = ((kraj = clock())-poc)) < INF) {
           if(kbhit()) {
              char ch = getch();
              if(toupper(ch) == 'A') { if(okdir(0, a)) movedir(0, a);}
              else if(toupper(ch) == 'D') { if(okdir(1, a)) movedir(1, a);}
              else if(toupper(ch) == 'S') {
                if(okdir(2, a)) movedir(2, a);
                else {
                    if(lock(a)) return 1;
                    break;
                }
              }
              else if(toupper(ch) == 'W') {if(okrotate(a)) rotate(a);}
              else if(toupper(ch) == 'P') {
                  double pdur = clock();
                  paused = true;
                  print(a);
                  while(toupper(getch()) != 'P') ;
                  paused = false;
                  print(a);
                  poc+=(clock()-pdur);
              }
           }
           if((int)j/ms_delay > last) {
               ++last;
               if(okdir(2, a)) movedir(2, a);
               else {
                    if(lock(a)) return 1;
                    break;
               }
           }

        }

        return 0;
    }
    void start() {
        init();
        nextp = getnext();
        playintro();
        for(;;) {
            thisp = nextp;
            nextp = getnext();
            pattern a(thisp, *this);
            print(a);
            if(run1(a)) break;

        }
        printover();
    }
    tetris() {
        c1 = '\0' + 219;
        c2 = '\0' + 178;
        c3 = '\0' + 177;
        ncut = 0; mincut = INF; blink = 0;
        ms_jump = 60;
        ms_delay = 800;
        ms_poc = 800;
        getseed();
        ifstream input("tetriminos.txt", ios::in);
        for(;;) {
            pair<string, patt> par;
            string s;
            patt p;
            input >> s;
            if(s == "end") break;
            par.first = s;
            for(int i = 0; i < 4; ++i)
              for(int j = 0; j < 4; ++j)
                 input >> par.second.pos[i][j];
            oblici.insert(par);
            lobl.push_back(s);
        }
        maxobl = lobl.size();
        todir[0][0] =  0; todir[0][1] = -1;   //lijevo
        todir[1][0] =  0; todir[1][1] =  1;   //desno
        todir[2][0] = -1; todir[2][1] =  0;   //dolje
    }
};
pattern::pattern(string s, tetris& tetr) {
    y = MAX_H-1;
    x = H_CENT;
    smjer = 0;
    miter iter = tetr.oblici.find(s);
    for(int i = 0; i < 4; ++i)
      for(int j = 0; j < 4; ++j)
        pos[i][j] = iter->second.pos[i][j];
}
int main() {
    //keybd_event(VkKeyScan('A'),0x9e,0 , 0);

    tetris igra;
    igra.start();

    return 0;
}
