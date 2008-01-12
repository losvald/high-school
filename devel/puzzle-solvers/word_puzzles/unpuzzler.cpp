/*
 * unpuzzler.cpp
 *
 * Copyright (C) 2008 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Word Games Unpuzzler.
 *
 * Word Games Unpuzzler is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Word Games Unpuzzler is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Word Games Unpuzzler. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#define MIN_LEN 3 /*min duljina rijeci*/
#define MAX_LEN 26 /*max duljina rijeci*/
#define MAX_WORDS 600000 /*max broj rijeci*/
#define MAX_DISPLAY_LIST 75 /*kolko zelis da ti izlista rezultata*/
#define FC(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
using namespace std;
vector<string> v, res;
int used[256];
int perm_len, was[256];
string perm_word;
struct elem {
  int words;
  int pref;
  elem *next[26];
  elem() {
    words = pref = 0;
    for(int i = 0; i < 26; ++i)
      next[i] = NULL;
  }
};
struct trie {
  elem *root;
  int count_pref(elem *node, const string& s) {
    if(s.empty()) return node->pref;
    char c = s[0]-'a';
    if(node->next[c] == NULL) return 0;
    return count_pref(node->next[c], s.substr(1, s.size()-1));
  }
  int count_words(elem *node, const string& s) {
    if(s.empty()) return node->words;
    char c = s[0]-'a';
    if(node->next[c] == NULL) return 0;
    return count_words(node->next[c], s.substr(1, s.size()-1));
  }
  void insert(elem *node, const string& s) {
    if(s.empty()) {
      ++node->words;
      return ;
    }
    else {
      char c = s[0]-'a';
      ++node->pref;
      if(node->next[c] == NULL)
        node->next[c] = new elem();
      insert(node->next[c], s.substr(1, (int)s.size()-1));
    }
  }
  trie() {
    root = new elem();
  }
} tr;
struct boggle {
  char grid[5][5];
  int n, bio[5][5];
  bool ok(int y, int x) { return y >= 0 && y < n && x >= 0 && x < n; }
  void dfs(int y, int x, elem *node, const string& s) {
    static const int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
    static const int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
    if(node->words)
      res.push_back(s);
    for(int i = 0; i < 8; ++i) {
      int nx = x + dx[i], ny = y + dy[i];
      if(ok(ny, nx) && !bio[ny][nx]) {
        char c = grid[ny][nx] - 'a';
        if(node->next[c] == NULL) continue;
        string t = s;
        t += grid[ny][nx];
        bio[ny][nx] = 1;
        dfs(ny, nx, node->next[c], t);
        bio[ny][nx] = 0;
      }
    }
  }
  void solve(const string& s) {
    for(n = 0; n*n < (int)s.size(); ++n) ;
    for(int i = 0; i < (int)s.size(); ++i)
      grid[i/n][i%n] = s[i];
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j)
        if(!bio[i][j]) {
          bio[i][j] = 1;
          string t(1,grid[i][j]);
          if(tr.root->next[t[0]-'a'] != NULL)
            dfs(i, j, tr.root->next[t[0]-'a'], t);
          bio[i][j] = 0;
        }
    }
  }

} b;
void set_search(const string& x) {
  printf("Set searching {%s}...\n", x.c_str());
  memset(used, 0, sizeof used);
  for(int i = 0; i < (int)x.size(); ++i) used[x[i]] = 1;
  for(int i = 0; i < (int)v.size(); ++i) {
    int ok = 1;
    for(int j = 0; j < (int)v[i].size(); ++j)
      if(!used[ v[i][j] ]) {
        ok = 0;
        break;
      }
    if(ok) res.push_back(v[i]);
  }
}
void permute(elem *node, const string& s) {
  if(node->words)
    res.push_back(s);
  for(int i = 0; i < perm_len; ++i)
    if(!was[i] && node->next[perm_word[i]-'a'] != NULL) {
      was[i] = 1;
      permute(node->next[perm_word[i]-'a'], s+perm_word[i]);
      was[i] = 0;
    }
}
void perm_search(const string& x) {
  printf("Perm searching (%s)...\n", x.c_str());
  memset(was, 0, sizeof was);
  perm_word = x;
  perm_len = x.size();
  for(int i = 0; i < perm_len; ++i)
    if(tr.root->next[perm_word[i]-'a'] != NULL) {
      was[i] = 1;
      string t;
      t += perm_word[i];
      permute(tr.root->next[t[0]-'a'], t);
      was[i] = 0;
    }
}
void begin_search(const string& x) {
  printf("Begin searching (%s)...\n", x.c_str());
  for(int i = 0; i < (int)v.size(); ++i) {
    if(v[i].substr(0, x.size()) == x)
      res.push_back(v[i]);
  }
}
int wild_eq(const string& a, const string& b) {
  if(a.size() != b.size()) return 0;
  for(int i = 0; i < (int)a.size(); ++i)
    if(a[i] != b[i] && a[i] != '?' && b[i] != '?')
      return 0;
  return 1;
}
void wildcard_search(const string& x) {
  printf("Wildcard searching (%s)...\n", x.c_str());
  FC(it, v) {
    if(wild_eq(*it, x))
      res.push_back(*it);
  }
}
void end_search(const string& x) {
  printf("End searching (%s)...\n", x.c_str());
  for(int i = 0; i < v.size(); ++i) {
    if(v[i].size() >= x.size() && string(v[i].end()-x.size(), v[i].end()) == x)
      res.push_back(v[i]);
  }
}
bool cmpf(const string& a, const string& b) {
  if(a.size() == b.size()) return a < b;
  return a.size() > b.size();
}
void output() {
  sort(res.begin(), res.end(), cmpf);
  res.erase(unique(res.begin(), res.end()), res.end());
  printf("Results (%d) - showing first %d:\n----------\n",
         (int)res.size(), MAX_DISPLAY_LIST);
  for(int i = 0; i < res.size() && i < MAX_DISPLAY_LIST; ++i) {
    printf("%s\n", res[i].c_str());
  }
}
void foutput() {
  FILE *out = fopen("word_out.txt", "w");
  sort(res.begin(), res.end(), cmpf);
  res.erase(unique(res.begin(), res.end()), res.end());
  FC(it, res)
    fprintf(out, "%s\n", it->c_str());
  fclose(out);
  printf("Wrote %d words to words_out.txt\n", (int)res.size());
}
int input() {
  res.clear();
  string s;
  cin >> s;
  if(s[0] == '{') set_search(string(s.begin()+1, s.end()-1));
  else if(s[0] == '(') perm_search(string(s.begin()+1, s.end()-1));
  else if(s[s.size()-1] == '-') begin_search(string(s.begin(), s.end()-1));
  else if(s[0] == '-') end_search(string(s.begin()+1, s.end()));
  else if(s[0] == '[') b.solve(string(s.begin()+1, s.end()-1));
  else wildcard_search(s);
  return 1;
}
void init() {
  printf("Loading...\n");
  static char buff[60];
  //v.reserve(MAX_WORDS);
  //printf("Odaberi rjecnik:\n0 - SCOWD\t1 - SOWPOD\n");
  //scanf("%d", &odabir);
  FILE *in = fopen("common_words.txt", "r");
  while( fscanf(in, "%s", buff) == 1 ) {
    if(strlen(buff) >= MIN_LEN && strlen(buff) <= MAX_LEN) {
      int ok = 1;
      for(int i = strlen(buff)-1; i >= 0; --i) {
        buff[i] = tolower(buff[i]);
        if(!isalpha(buff[i])) ok = 0;
      }
      if(!ok) continue;
      v.push_back(buff);
      tr.insert(tr.root, buff);
    }
  }
  fclose(in);
  printf("%d words loaded.\n", (int)v.size());
  printf("Sorting...");
  sort(v.begin(), v.end());
  printf("done.\n");
}
int main() {

  for( init(); printf("Query:\n") && input(); output(), foutput() ) ;

  return 0;
}
