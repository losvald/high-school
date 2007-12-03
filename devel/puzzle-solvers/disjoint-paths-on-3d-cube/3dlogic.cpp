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
#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <queue>
#include <algorithm>
#define WALL '#'
#define MAX 6
#define FC(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
using namespace std;
int n, start_path[26], end_path[26];
char cube[2*MAX+1][2*MAX+1];
int polje[3*MAX*MAX+1], bfs_dist[3*MAX*MAX+1];
vector<list<int> > adj;
vector<int> colors, best_perm;
int tot_space, extra_space, last_color;
int min_space[26], min_path[26];
double stcl, last_cl, max_time, best_time = 10E20;
int fctrl, skip;
int brojac;
struct point {
  int x, y;
  point() { }
  point(const int x, const int y) : x(x), y(y) {}
};
int hc(const int y, const int x) {
  if(y < n || x < n) return y*n + x;
  return 2*n*n + (y-n)*n+(x-n);
}
void print() {
  for(int i = 0; i < 2*n; ++i, printf("\n"))
    for(int j = 0; j < 2*n; ++j) {
      if(i < n && j >= n) break;
      printf("%c", polje[hc(i, j)]);
    }
}
int bfs(const int color) {
  memset(bfs_dist, -1, sizeof bfs_dist);
  bfs_dist[start_path[color]] = 0;
  queue<int> q;
  for(q.push(start_path[color]); !q.empty(); q.pop()) {
    int x = q.front();
    if(x == end_path[color]) break;
    FC(it, adj[x]) {
      if(bfs_dist[*it] != -1) continue;
      if(polje[*it] != '.' && polje[*it] != 'A'+color) continue;
      bfs_dist[*it] = bfs_dist[x] + 1;
      q.push(*it);
    }
  }
  if(bfs_dist[end_path[color]] == -1) return -1;
  return bfs_dist[end_path[color]]+1;
}
void info(const int x, const int d, const int col) {
  //if(clock()-last_cl > 5000) {
    last_cl = clock();
    printf("%d. (%3d %3d %3d)\n", brojac++, x, d, col);
    print();
  //}
  cin.get();
}
int blockable(const int d, const int col) {//dal su zablokirani ostali putevi
  int paths_after = 0;
  for(int i = col+1; i < colors.size(); ++i) {
    int curr_path = bfs(colors[i]);
    if(curr_path == -1) return 1; //izadji ak ovo blokira ostale puteve
      paths_after += curr_path;
      if(d+paths_after - min_space[i] > extra_space) {
        //printf("*");
        return 1;
      }
  }
  return 0;
}
int collides(const int x, const char c) {
  int cnt = 0;
  FC(it, adj[x])
    if(polje[*it] == c)
      ++cnt;
  return cnt >= 2;
}
int dfs(const int x, const int d, const int col) {
  ++brojac;
  if(brojac%50 && clock()-stcl > max_time) return 0;
  if(x == end_path[last_color]) return 1;
  if(d - min_space[col] > extra_space) return 0;
  if( collides(x, 'a' + colors[col]) ) return 0;
  if(blockable(d, col) ) return 0;
  if(x == end_path[colors[col]]) {
    //info(x, d, col);
    if( dfs(start_path[colors[col+1]], d+1, col+1) ) return 1;
    return 0;
  }
  if(x != start_path[colors[col]]) polje[x] = 'a' + colors[col];
  //printf("[%d %d %c]\n", x, d, 'A'+colors[col]); print(); cin.get();
  FC(it, adj[x]) {
    if(polje[*it] == '.' || polje[*it] == 'A'+colors[col] && *it != start_path[colors[col]])
      if( dfs(*it, d+1, col) )
        return 1;
  }
  if(x != start_path[colors[col]]) polje[x] = '.';
  return 0;
}
void clear_paths() {
  for(int i = 0; i < 2*n; ++i)
    for(int j = 0; j < 2*n; ++j) {
      if(i < n && j >= n) break;
      polje[hc(i, j)] = cube[i][j];
    }
}
void solve() {
  sort(colors.begin(), colors.end());
  for(int curr_perm = 0; ; curr_perm += skip) {
    last_cl = stcl = clock();
    extra_space = tot_space;
    int last_space = 0;
    FC(it, colors) {
      min_path[it-colors.begin()] = bfs(*it);
      extra_space -= min_path[it-colors.begin()];
      last_space = min_space[it-colors.begin()] = min_path[it-colors.begin()] + last_space;
    }
    last_color = colors[colors.size()-1];
    int sol = dfs(start_path[colors[0]], 1, 0);
    double ccl = clock()-stcl;
    double percent = 100.00 * curr_perm / fctrl ;
    if(ccl < max_time)
      printf("\n%6d => %d (= %lf ms) ... %lf%% complete\n", curr_perm, sol, ccl, percent);
    else if(!sol)
      printf("\n%6d NONE  (= %lf ms) ... %lf%% complete\n", curr_perm, ccl, percent);
    if(sol) {
      print();
      if(ccl < best_time) {
        best_time = ccl;
        best_perm = colors;
      }
      break ;
    }
    clear_paths();
    int quit = 0;
    for(int i = 0; i < skip; ++i) {
      if(!next_permutation(colors.begin(), colors.end())) {
        quit = 1;
        break;
      }
    }
    if(quit) break;
  }
  printf("\nBest time: %lf\nBest permutation: ", best_time);
  FC(it, best_perm) printf("%c", 'A'+*it);
}
int fact(int x) { return (x > 1) ? x*fact(x-1) : 1; }
void prepare() {
  const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
  memset(start_path, -1, sizeof start_path);
  memset(end_path, -1, sizeof end_path);
  adj.resize(3*n*n);
  for(int i = 0; i < 2*n; ++i) {
    for(int j = 0; j < 2*n; ++j) {
      if(i < n && j >= n) break;
      polje[hc(i, j)] = cube[i][j];
      if(cube[i][j] == WALL) continue;
      for(int sm = 0; sm < 4; ++sm) {
        int ny = i + dy[sm], nx = j + dx[sm];
        if(ny < 0 || ny >= 2*n || nx < 0) continue;
        if(ny < n && nx >= n || ny >= n && nx >= 2*n) continue;
        if(cube[ny][nx] == WALL) continue;
        int c1 = hc(i, j), c2 = hc(ny, nx);
        adj[c1].push_back(c2);
      }
      if(i < n && j == n-1) {
        int ny = j+1, nx = 2*n-i-1;
        if(cube[ny][nx] != WALL) {
          int c1 = hc(i, j), c2 = hc(ny, nx);
          adj[c1].push_back(c2);
          adj[c2].push_back(c1);
        }
      }
      if(cube[i][j] >= 'A' && cube[i][j] <= 'Z') {
        if(start_path[cube[i][j]-'A'] == -1)
          start_path[cube[i][j]-'A'] = hc(i, j);
        else
          end_path[cube[i][j]-'A'] = hc(i, j);
      }
      ++tot_space;
    }
  }
  for(int i = 0; i < 26; ++i)
    if(start_path[i] != -1)
      colors.push_back(i);

  printf("How many seconds to wait? ");
  scanf("%lf", &max_time); max_time *= 100;
  max_time /= (double) (fctrl = fact(colors.size()));
  printf("Try every which permutation? ");
  scanf("%d", &skip); max_time *= skip;
  printf("[[[[%lf]]]]", max_time);
}
void input() {
  scanf("%d\n", &n);
  for(int i = 0; i < 2*n; ++i) gets(cube[i]);
}
int main() {
  input();
  prepare();
  solve();
  printf("\n\nDone!\n");
  scanf("\n");
  return 0;
}
/*
3
...
RB.
...
.##.#.
.#BR.#
......
*/
/*
 0  1  2
 3  4  5
 6  7  8
 9 10 11 18 19 20
12 13 14 21 22 23
15 16 17 24 25 26
*/

/*
2
A.
#B
..#.
AB..

2
A#
B#
B#..
A#..

5
....#
....#
....#
....#
#####
....C.....
.B.....A..
....CD...#
........D.
A........B

aaa.Cdddd.
aBa.cd.Ad.
aba.CD.ad#
abaaaaaaD.
AbbbbbbbbB

5
...IW
.GH..
..I.W
H..G#
....#
....A.....
.B.....C..
....AD...#
........D.
C........B

5
##A##
B...B
##.##
##A##
#####
##########
##########
##########
##########
##########

*/
/* LEVEL 29
6
......
..P.Y.
......
....R.
..W...
......
..B..G...B..
.......P.W..
...O........
......G...O.
.........R..
.......Y....
*/
/*
5
#..Y#
.....
.....
..B..
..R..
.....P...#
...Y..R..B
.ZC.....Z.
.....C....
P........#





*/
