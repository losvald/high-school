/*
 * con4_fixedheight.cpp
 *
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Connect4.
 *
 * Connect4 is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Connect4 is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect4. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#define MAX 7
#define ROW 6
#define VIS 42
#define UNDEF 1000
#define MAXH 514229
using namespace std;
int maxi, tot;
list<pair<unsigned long long, int> > hash[MAXH];
static int br = 0, found = 0;
long long board; //ploca
//visina pojedinog stupca u ploci
int eight[MAX] = {0x0, 0x8, 0x10, 0x18, 0x20, 0x28, 0x30}; //0, 8, 16, 24...
map<unsigned long long, int> memo;
int start, offset;
inline int get_vis(int x) {return ((board >> VIS) & (07 << 3*x)) >> 3*x; }
inline bool ok_vis(int x) { return (((board >> VIS) & (07 << 3*x)) >> 3*x) < ROW; }
void print() {
  static const char color[] = "XO";
  for(int i = ROW-1; i >= 0; --i) {
    printf("%c", 179);
    for(int j = 0; j < MAX; ++j) {
      if(get_vis(j) > i)
        printf("%c", color[((1ULL << (i + eight[j])) & board) > 0]);
      else printf(".");
    }
    printf("%c\n", 179);
  }
  //printf("%c%c%c%c%c%c%c%c%c\n", 195,196,196,196,196,196,196,196,180);
  //printf("%c1234567%c\n", 179,179);
  printf("%c%c%c%c%c%c%c%c%c\n", 192,196,196,196,196,196,196,196,217);
}
bool check(int boja) {
  for(int st = 0; st < MAX; ++st) {
    for(int i = 0; i <= get_vis(st) - 4; ++i) {
      if(boja) {
        if(!((0xFULL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0xFULL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i));
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x1010101ULL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x1010101ULL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i)-i);
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x8040201ULL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x8040201ULL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i)-(3-i));
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x1020408ULL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x1020408ULL << (i + eight[st])) & board)) return false;
    }
  }
  return true;
}
bool ok(int boja) {
  return check(boja ^ 1);
}
void ubaci(int x, int boja) {
  if(boja) board |= 1ULL << (eight[x] + get_vis(x));
  printf("[\n%20d + \n%20d =\n", int(board >> VIS), int((1ULL << (3*x + VIS)) >> VIS));
  board += 1ULL << (3*x + VIS);
  printf("%d ]", int(board >> VIS));
  printf("[[%llo - %lld]\n", 1ULL << (3*x + VIS), 1ULL << (3*x + VIS));
}
void izbaci(int x) {
  board &= ~(1ULL << (eight[x] + get_vis(x)-1));
  board -= ((1ULL << 3*x) << VIS);
}
int ins_hash(unsigned long long& x, int v) {
  hash[x%MAXH].push_back( make_pair(x, v) );
  return v;
}
bool find_hash(unsigned long long& x) {
  int y = x%MAXH;
  for(list<pair<unsigned long long, int> >::iterator it = hash[y].begin(); it != hash[y].end(); ++it)
    if(it->first == x) return true;
  return false;
}
int get_hash(unsigned long long& x) {
  int y = x%MAXH;
  for(list<pair<unsigned long long, int> >::iterator it = hash[y].begin(); it != hash[y].end(); ++it)
    if(it->first == x) return it->second;
  return 2*UNDEF;
}
int rec(int k) {
  //k&1 - ne-komp
  unsigned long long stanje = board;
  if(find_hash(stanje)) {++found; return get_hash(stanje); }
  if(!ok(k&1)) {//ako je game over
    if(k&1) return ins_hash(stanje, 100-k); //ako je pobjeda
    return ins_hash(stanje, -(100-k));
  }
  if(k > 9) return 0;
  int worst = UNDEF, best = -UNDEF;
  for(int i = 0; i < MAX; ++i) {
    if(!ok_vis(i)) continue;
    ubaci(i, k&1);
    int x = rec(k+1);
    if(k&1) {//ako ne igra komp onda se ne-komp zeli pobijedit tj imat 0
      worst = min(worst, x);
    }
    else {//ako igra komp zeli da pobijedi tj. imat 2
      best = max(best, x);
    }
    izbaci(i);
  }
  if(k&1) {
    if(worst == UNDEF) return ins_hash(stanje, 0);
    return ins_hash(stanje, worst);
  }
  if(best == -UNDEF) return ins_hash(stanje, 0);
  return ins_hash(stanje, best);
}
int get_hint(int boja) {
  int ret = 0;
  vector<pair<int, int> > v;
  vector<pair<int, int> >::iterator it;
  if(!boja) printf("\rHint: %3d%%", 0);
  else printf("\rThinking: %3d%%", 0);
  for(int j = 0; j < 7; ++j) {
    if(!ok_vis(j)) {
      continue; }
    ubaci(j, boja ^ 1);
    int x = rec(boja);
    v.push_back(make_pair(x, j));
    izbaci(j);
    if(!boja) printf("\rHint: %3d%%", int(100*((j+1)/7.0)));
    else printf("\rThinking: %3d%%", int(100*((j+1)/7.0)));
  }
  if(boja) sort(v.begin(),v.end(), greater<pair<int, int> >());
  else sort(v.begin(), v.end());
  for(it = v.begin(); it != v.end() && it->first == v[0].first; ++it) ;
  v.erase(it, v.end());
  return v[0].second;
}
void save_game() {
  ofstream file_out("save.dat", ios::out);
  file_out << board << endl;
  file_out.close();
  printf("Game saved.\n");
}
int input(int boja) {
  int x;
  for(char s[20];;) {
    printf("Upisi potez (1-7 ili \"save\"): ");
    scanf("%s", s);
    if(strcmp(s, "save") == 0) { save_game(); continue; }
    x = s[0]-'0';
    if(x > 0) {
      if(ok_vis(x-1)) break;
      continue;
    }
    else if(x < 0) continue;
    printf("\rHint: %d        \n", get_hint(boja)+1);
  }
  return x;
}
int play() {
  printf("%llo", board >> VIS);
  int curr;
  print();
  start = 1;
  for(curr = 0; /*(board >> VIS) == 06666666*/; curr) {
    int hint = 3;
    for(int i = 0; i < 7; ++i) printf("%d", get_vis(i));
    printf("(%llo)\n", board >> VIS);

    for(int i = 0; i < MAXH; ++i) hash[i].clear();
    maxi = 0; tot = 0;
    if(curr&1) {
      double strt = clock();
      if(curr != start) hint = get_hint(curr&1);
      ubaci(hint, 0);
      printf("\rKompov potez: %d       \n", hint+1);
      for(int i = 0; i < MAXH; ++i) {
        maxi = max(maxi, (int)hash[i].size());
        tot += hash[i].size();
      }
      printf("(%lf ms)\n(max = %d/%d)\n", clock()-strt, maxi, tot);
    }
    else {
      int x = input(curr&1);
      ubaci(x-1, 1);
    }
    print();
  }
  printf("Igra je gotova!\n");
  if((board >> VIS) == 06666666) return -1;
  return curr & 1;
}
void print_game_over(int winner) {
  if(winner == -1) printf("Nerjeseno!\n");
  else if(winner) printf("Pobjeda!\n");
  else printf("Loser!\n");
}
void load_saved() {
  ifstream file_in("save.dat", ios::in);
  if(file_in.is_open()) {
    printf("Load OK.\n");
    file_in >> board;
    file_in.close();
    start = 0;
    offset = 2;
  }
  else printf("Error!\n");
}
void load_my_game() {
  printf("Upisi igru kakvu zelis (bez \"), 6 redaka po 7 znakova:\n");
  printf("'.' - prazno\t'X' - komp, 'O' - ti\nnpr.\"\n");
  printf(" .......\n .......\n .1.0...\n");
  printf(" .1.1...\n 10.00..\n 00.110.\"\n");
  printf("i onda (bez \"):\n \"1\" - ako je tvoj potez\n\"2\" - ako je kompov potez\n");
  char s[10][10];
  for(int i = 0; i < ROW; ++i) scanf("%s", s[i]);
  for(int i = ROW-1; i >= 0; --i) {
    for(int j = 0; j < MAX; ++j) {
      if(s[i][j] == 'O') ubaci(j, 1);
      else if(s[i][j] == 'X') ubaci(j, 0);
    }
  }
  printf("Load ok!\n");
  scanf("%d", &start); offset = 1;
  printf("Load ok!\n");
}
void load() {
  printf("1 - Load Saved Game\n2 - Load nastimane igre\n");
  int upit; scanf("%d", &upit);
  if(upit == 1) load_saved();
  else load_my_game();
}
void init() {board = 0ULL;}
int main() {
  srand(time(0));
  double st = clock();
  for(;;) {
    init();
    printf("1 - New Game\t2 - Load Game\n\t3 - Quit\n");
    int upit; scanf("%d", &upit);
    if(upit == 3) break;
    else if(upit == 2) load();
    else { start = rand()&1; offset = 0; }
    print_game_over(play());
  }
  printf("%d (%d)\n%lf", br, found, clock()-st);
  scanf("\n");
  return 0;
}
/*
.......
.......
.O.X...
.O.O...
OX.XX..
XX.OOX.

.......
.......
.O.X...
.O.OO..
OX.XX.O
XX.OOXO

tricky slucaj:

...O...
...O...
.O.XO..
.O.OO..
OX.XX.O
XX.OOXO

OOOXXO.
XXXOOOX
OOOXXXO
XXXOOOX
OOOXXXO
XXXOOOX
*/
