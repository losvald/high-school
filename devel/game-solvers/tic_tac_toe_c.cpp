/*
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
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
#define MAX 3
int a[MAX][MAX], pobjednik = -1;
void print() {
  for(int i = 0; i < MAX; ++i)
    for(int j = 0; j < MAX; ++j) {
      if(a[i][j] == 1) printf("O");
      else if(a[i][j] == 2) printf("X");
      else printf(" ");
      if(j < MAX-1) printf("|");
      else printf("\n");
    }
}
bool ok(int pos) {
  int x = pos % MAX, y = pos / MAX;
  return x >= 0 && x < MAX && y >= 0 && y < MAX && !a[y][x];
}
void postavi(int pos, int tko) { a[pos/MAX][pos%MAX] = tko + 1; }
void makni(int pos) { a[pos/MAX][pos%MAX] = 0; }
int game_over(int pos) {
  int x = pos % MAX, y = pos / MAX;
  if(a[0][x] == a[1][x] && a[1][x] == a[2][x]) return a[0][x];
  if(a[y][0] == a[y][1] && a[y][1] == a[y][2]) return a[y][0];
  if(x+y == MAX-1 && a[2][0] == a[1][1] && a[1][1] == a[0][2]) return a[2][0];
  if(x+MAX-y-1 == MAX-1 && a[0][0] == a[1][1] && a[1][1] == a[2][2]) return a[0][0];
  for(int i = 0; i < MAX; ++i)
    for(int j = 0; j < MAX; ++j)
      if(a[i][j] <= 0) return -1;
  return 0;
}
int probaj(int tko) {
  int best = -1;
  for(int i = 0; i < MAX*MAX; ++i) {
    if(!ok(i)) continue;
    postavi(i, tko);
    int winner = game_over(i), r;
    if(winner > 0) r = 1;
    else if(winner == 0) r = 0;
    else r = probaj(1-tko);
    makni(i);
    if (r > best) best = r;
  }
  return -best;
}
int main() {
  for(int turn = 0, gdje; pobjednik == -1; ++turn, pobjednik = game_over(gdje)) {
    int tko = turn % 2;
    if(!tko) {
      printf("Your turn!\n");
      do {
        printf("Enter a move [1-%d]: ", MAX*MAX);
        scanf("%d", &gdje);
      } while(!ok(--gdje));
    }
    else {
      printf("Computer's turn!\n");
      int best = -1, curr;
      for(int i = 0; i < MAX*MAX; ++i) {
        if(!ok(i)) continue;
        postavi(i, 1);
        pobjednik = game_over(i);
        if(pobjednik > 0) curr = 1;
        else if(pobjednik == 0) curr = 0;
        else curr = probaj(0);
        makni(i);
        if(curr > best) {
          best = curr;
          gdje = i;
        }
      }
    }
    postavi(gdje, tko);
    //nema clear screena
    print();
  }
  printf("\n");
  if (pobjednik == 0) printf("Tie\n");
  else if (pobjednik == 1) printf("You won!\n");
  else if (pobjednik == 2) printf("You lost!");

  scanf("\n");
  return 0;
}
