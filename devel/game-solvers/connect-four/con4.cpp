/*
 * con4.cpp
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
#define UNDEF 1000
#define MAXH 514229
using namespace std;
typedef pair<long long, int> key;
list<pair<key, int> > hash[MAXH];
long long board; //ploca
int visina; //visina pojedinog stupca u ploci
int eight[MAX] = {0x0, 0x8, 0x10, 0x18, 0x20, 0x28, 0x30}; //0, 8, 16, 24...
int start, offset; //tko je prvi na potezu
inline int get_vis(int x) {return (visina & (0xF << 4*x)) >> 4*x; } //visina x-tog stupca
inline bool ok_vis(int x) { return ((visina & (0xF << 4*x)) >> 4*x) < ROW; }
void print() {
  static const char color[] = "XO";
  for(int i = ROW-1; i >= 0; --i) {
    printf("%c", 179);
    for(int j = 0; j < MAX; ++j) {
      if(get_vis(j) > i)
        printf("%c", color[((1LL << (i + eight[j])) & board) > 0]);
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
        if(!((0xFLL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0xFLL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i));
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x1010101LL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x1010101LL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i)-i);
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x8040201LL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x8040201LL << (i + eight[st])) & board)) return false;
    }
  }
  for(int st = 0; st < MAX-3; ++st) {
    int minh = 10;
    for(int i = 0; i < 4; ++i) minh = min(minh, get_vis(st+i)-(3-i));
    for(int i = 0; i < minh; ++i) {
      if(boja) {
        if(!((0x1020408LL << (i + eight[st])) & ~board)) return false;
      }
      else if(!((0x1020408LL << (i + eight[st])) & board)) return false;
    }
  }
  return true;
}
bool ok(int boja) {
  return check(boja ^ 1);
}
void ubaci(int x, int boja) {
  if(boja) board |= 1LL << (eight[x] + get_vis(x));
  visina += 1 << 4*x;
}
void izbaci(int x) {
  board &= ~(1LL << (eight[x] + get_vis(x)-1));
  visina -= 1 << 4*x;
}
int ins_hash(key& x, int v) {
  hash[(x.first+x.second)%MAXH].push_back( make_pair(x, v) );
  return v;
}
bool find_hash(key& x) {
  int y = (x.first+x.second)%MAXH;
  for(list<pair<key, int> >::iterator it = hash[y].begin(); it != hash[y].end(); ++it)
    if(it->first == x) return true;
  return false;
}
int get_hash(key& x) {
  int y = (x.first+x.second)%MAXH;
  for(list<pair<key, int> >::iterator it = hash[y].begin(); it != hash[y].end(); ++it)
    if(it->first == x) return it->second;
  return 2*UNDEF;
}
int rec(int k) {
  //k&1 - ne-komp
  key stanje = make_pair(board, visina);
  if(find_hash(stanje)) return get_hash(stanje);
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
  return v[rand()%v.size()].second;
}
void save_game() {
  ofstream file_out("save.dat", ios::out);
  file_out << board << endl <<  visina << endl;
  file_out.close();
  printf("Game saved.\n");
}
int input(int boja) {
  int x;
  for(char s[20];;) {
    printf("Enter move (1-7 or \"save\" or \"exit\"): ");
    scanf("%s", s);
    if(strcmp(s, "save") == 0) { save_game(); continue; }
    else if(strcmp(s, "exit") == 0) return UNDEF;
    else if(s[0] < '0' || s[0] > '7') continue;
    x = s[0]-'0';
    if(x > 0) {
      if(ok_vis(x-1)) break;
      continue;
    }
    printf("\rHint: %d        \n", get_hint(boja)+1);
  }
  return x;
}
int play() {
  int curr;
  print();
  for(curr = start+offset; ok((curr&1)^1) && visina != 0x6666666; ++curr) {
    int hint = 3;
    for(int i = 0; i < MAXH; ++i) hash[i].clear();
    if(curr&1) {
      double strt = clock();
      if(curr != start) hint = get_hint(curr&1);
      ubaci(hint, 0);
      printf("\rComputer's move: %d       \n", hint+1);
    }
    else {
      int x = input(curr&1);
      if(x == UNDEF) return 0;
      ubaci(x-1, 1);
    }
    print();
  }
  printf("Game over!\n");
  if(visina == 0x6666666) return -1;
  return curr & 1;
}
void print_game_over(int winner) {
  if(winner == -1) printf("Tie!\n");
  else if(winner) printf("You won!\n");
  else printf("Loser!\n");
}
void load_saved() {
  ifstream file_in("save.dat", ios::in);
  if(file_in.is_open()) {
    printf("Load OK.\n");
    file_in >> board >> visina;
    file_in.close();
    start = 0;
    offset = 2;
  }
  else {
    printf("Error! Missing \"save.dat\". Starting a new game...\n");
    start = rand()&1; offset = 0;
  }
}
void load_my_game() {
  printf("Enter a custom game (w/o \"), in 6 rows containing 7 characters:\n");
  printf("'.' - prazno\t'X' - komp, 'O' - ti\ne.g.,\"\n");
  printf(" .......\n .......\n .1.0...\n");
  printf(" .1.1...\n 10.00..\n 00.110.\"\n");
  printf("then (w/o \"):\n \"1\" - if it's your turn\n\"2\" - if it's computer's turn\n");
  char s[10][10];
  for(int i = 0; i < ROW; ++i) scanf("%s", s[i]);
  for(int i = ROW-1; i >= 0; --i) {
    for(int j = 0; j < MAX; ++j) {
      if(s[i][j] == 'O') ubaci(j, 1);
      else if(s[i][j] == 'X') ubaci(j, 0);
    }
  }
  scanf("%d", &start); offset = 1;
  printf("Load ok!\n");
}
void load() {
  printf("1 - Load Saved game\n2 - Load Custom game\n");
  int upit; scanf("%d", &upit);
  if(upit == 1) load_saved();
  else load_my_game();
}
void init() {board = 0LL, visina = 0; }
int main() {
  srand(time(0));
  printf("Connect Four v0.8 by Leo\n\n");
  for(;;) {
    init();
    printf("1 - New Game\t2 - Load Game\n\t3 - Quit\n");
    int upit; scanf("%d", &upit);
    if(upit == 3) break;
    else if(upit == 2) load();
    else { start = rand()&1; offset = 0; }
    print_game_over(play());
  }
  return 0;
}
